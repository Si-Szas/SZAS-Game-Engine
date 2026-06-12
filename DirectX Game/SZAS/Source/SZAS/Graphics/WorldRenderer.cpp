#include <SZAS/Graphics/WorldRenderer.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/Graphics/DeviceContext/DeviceContext.h>
#include <SZAS/Graphics/SwapChain/SwapChain.h>
#include <SZAS/Time/EngineTime.h>
#include <SZAS/Graphics/VertexBuffer/VertexBuffer.h>
#include <SZAS/Graphics/ConstantBuffer/ConstantBuffer.h>
#include <SZAS/Graphics/IndexBuffer/IndexBuffer.h>
//GAME AND WORLD HEADER//
#include <SZAS/Game/World.h>
//GAME OBJECTS//
#include <SZAS/AGameObject/AGameObject.h>
//COMPONENTS//
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/AComponent/TransformComponent.h>
#include <SZAS/AComponent/CubeComponent.h>

#include <SZAS/Math/Vec3.h>
#include <fstream>
#include <ranges>

szas::WorldRenderer::WorldRenderer(const WorldRendererDescriptor& descriptor) :
	Base(descriptor.base),
	m_graphicsDevice(descriptor.graphicsEngine)
{
	//Creates the deferred device context
	auto& device = m_graphicsDevice;
	m_deviceContext = device.CreateDeviceContext();

	//Define the Shader File Path
		// Relative paths are relative to the root of project folder (DirectX Game Folder)
	constexpr char vertexShaderFilePath[] = "SZAS/Assets/Shaders/VertexShader.hlsl";
	//Read the contents of the shader file
	std::ifstream vertexShaderStream(vertexShaderFilePath);
	if (!vertexShaderStream) SZASLogThrowError("Failed to open VertexShader.hlsl file.");
	//Retrieve file data. So calling Range would call the entire shader into a string
	std::string vertexShaderFileData{
		std::istreambuf_iterator<char>(vertexShaderStream),	//Beginning of the file
		std::istreambuf_iterator<char>()				//Beginning of the end
	};

	//Create a ShaderSourceCode using constexpr (evaluate value at compile time)
	auto vertexShaderSourceCode = vertexShaderFileData.c_str();
	auto vertexShaderSourceCodeSize = vertexShaderFileData.length();

	//Call our compile shader method, pass the shader we created
		//VERTEX SHADER
	auto vs = device.CompileShader({
		vertexShaderFilePath,
		vertexShaderSourceCode,
		vertexShaderSourceCodeSize,
		"VS_Main",
		ShaderType::VertexShader
	});

	//Define Shader File Path for Hull Shader
	constexpr char hullShaderFilePath[] = "SZAS/Assets/Shaders/HullShader.hlsl";
	std::ifstream hullShaderStream(hullShaderFilePath);
	if (!hullShaderStream) SZASLogThrowError("Failed to open HullShader.hlsl file.");

	std::string hullShaderFileData{
		std::istreambuf_iterator<char>(hullShaderStream),	//Beginning of the file
		std::istreambuf_iterator<char>()				//Beginning of the end
	};
	
	auto hullShaderSourceCode = hullShaderFileData.c_str();
	auto hullShaderSourceCodeSize = hullShaderFileData.length();

	//Compile Hull Shader
	auto hs = device.CompileShader({
		hullShaderFilePath,
		hullShaderSourceCode,
		hullShaderSourceCodeSize,
		"HS_Main",
		ShaderType::HullShader
		});

	//Define Shader File Path for Domain Shader
	constexpr char domainShaderFilePath[] = "SZAS/Assets/Shaders/DomainShader.hlsl";
	std::ifstream domainShaderStream(domainShaderFilePath);
	if (!domainShaderStream) SZASLogThrowError("Failed to open DomainShader.hlsl file.");

	std::string domainShaderFileData{
		std::istreambuf_iterator<char>(domainShaderStream),	//Beginning of the file
		std::istreambuf_iterator<char>()				//Beginning of the end
	};

	auto domainShaderSourceCode = domainShaderFileData.c_str();
	auto domainShaderSourceCodeSize = domainShaderFileData.length();

	//Compile Domain Shader
	auto ds = device.CompileShader({
		domainShaderFilePath,
		domainShaderSourceCode,
		domainShaderSourceCodeSize,
		"DS_Main",
		ShaderType::DomainShader
	});

	constexpr char pixelShaderFilePath[] = "SZAS/Assets/Shaders/PixelShader.hlsl";
	//Read the contents of the shader file
	std::ifstream pixelShaderStream(pixelShaderFilePath);
	if (!pixelShaderStream) SZASLogThrowError("Failed to open PixelShader.hlsl file.");
	//Retrieve file data. So calling Range would call the entire shader into a string
	std::string pixelShaderFileData{
		std::istreambuf_iterator<char>(pixelShaderStream),	//Beginning of the file
		std::istreambuf_iterator<char>()				//Beginning of the end
	};

	//Create a ShaderSourceCode using constexpr (evaluate value at compile time)
	auto pixelShaderSourceCode = pixelShaderFileData.c_str();
	auto pixelShaderSourceCodeSize = pixelShaderFileData.length();

	//PIXEL SHADER
	auto ps = device.CompileShader({
		pixelShaderFilePath,
		pixelShaderSourceCode,
		pixelShaderSourceCodeSize,
		"PS_Main",
		ShaderType::PixelShader
		});

	auto vertexShaderSignature = device.CreateVertexShaderSignature({vs});

	//Create Graphics Pipeline State
	m_pipeline = device.CreateGraphicsPipelineState({*vertexShaderSignature, *ps, *hs, *ds});

	////////////// CREATING QUADS //////////////
	//const Vertex quad1Vertices[] =
	//{
	//	/* BL */ { {-0.95f, 0.15f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
	//	/* TL */ { {-0.95f, 0.85f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} },
	//	/* BR */ { {-0.40f, 0.15f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
	//	/* TP */ { {-0.40f, 0.85f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f} }
	//};

	/// CREATING A 3D OBJECT //

	const Vertex cubeVertices[] =
	{
		{ {-0.5f,-0.5f,-0.5f},	{1,0,0,1}},
		{ {-0.5f,0.5f,-0.5f},	{0,1,0,1}},
		{ {0.5f,0.5f,-0.5f},	{0,0,1,1}},
		{ {0.5f,-0.5f,-0.5f},	{1,1,1,1}},
		  
		{ {0.5f,-0.5f,0.5f},	{0,0,0,1}},
		{ {0.5f,0.5f,0.5f},		{1,0,1,1}},
		{ {-0.5f,0.5f,0.5f},	{0,1,1,1}},
		{ {-0.5f,-0.5f,0.5f},	{1,1,0,1}}
	};

	//const ui32 indexList[] =
	//{
	//	//Front Face
	//	0, 1, 2,
	//	2, 3, 0,
	//	//Right Face
	//	3, 2, 5,
	//	5, 4, 3,
	//	//Left Face
	//	6, 1, 0,
	//	0, 7, 6,
	//	//Back Face
	//	7, 6, 5,
	//	5, 4, 7,
	//	//Top Face
	//	6, 5, 2, 
	//	2, 1, 6,
	//	//Bottom Face
	//	7, 0, 3,
	//	3, 4, 7
	//};

	//We are drawing in 4 control point patches
	const ui32 indexList[] =
	{
		//Front Face
		0, 1, 3, 2,
		//Back Face
		4, 5, 7, 6,
		//Top Face
		5, 2, 6, 1,
		//Bottom Face
		7, 0, 4, 3,
		//Right Face
		3, 2, 4, 5,
		//Left Face
		7, 6, 0, 1
	};

	//const Vertex quad2Vertices[] =
	//{
	//	/* BL */ { {-0.35f, -0.25f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
	//	/* TL */ { {-0.35f,  0.25f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
	//	/* BR */ { { 0.35f, -0.25f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} },
	//	/* TR */ { { 0.35f,  0.25f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} }
	//};
	//
	//const Vertex quad3Vertices[] =
	//{
	//	/* BL */ { {0.95f, -0.15f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
	//	/* TL */ { {0.95f, -0.85f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} },
	//	/* BR */ { {0.40f, -0.15f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} },
	//	/* TR */ { {0.40f, -0.85f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f} }
	//};
	//
	//m_quadList.push_back(new Quad(quad1Vertices, vertexShaderSignature, ps, hs, ds));
	//m_quadList.push_back(new Quad(quad2Vertices, vertexShaderSignature, ps, hs, ds));
	//m_quadList.push_back(new Quad(quad3Vertices, vertexShaderSignature, ps, hs, ds));

	//Gets the vertex data of all of the quads created
	//std::vector<Vertex> allQuadVertices;
	//for (size_t i = 0; i < m_quadList.size(); i++)
	//{
	//	const void* rawVertexData = m_quadList[i]->GetVertexList();
	//	const Vertex* vertexArray = static_cast<const Vertex*>(rawVertexData);
	//
	//	for (size_t k = 0; k < 4; k++)
	//	{
	//		allQuadVertices.push_back(vertexArray[k]);
	//	}
	//}
	////Total vertex count of the quads
	//UINT totalVertexCount = static_cast<UINT>(allQuadVertices.size());

	//Passes quads' vertices to vertex buffer
	//m_vertexBuffer = device.CreateVertexBuffer
	//({
	//	allQuadVertices.data(),
	//	totalVertexCount,  
	//	sizeof(Vertex)
	//});

	m_vertexBuffer = device.CreateVertexBuffer
	({
		cubeVertices,					//Vertex List
		std::size(cubeVertices),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
	});

	//Create constant buffer
	m_vsConstantBuffer = device.CreateConstantBuffer
	({
		&m_vsConstantBuffer,
		sizeof(ConstantData)
	});

	//We don't have any constant data to pass to the pixel shader
	m_psConstantBuffer = nullptr;

	m_indexBuffer = device.CreateIndexBuffer
	({
		indexList,//Index List
		std::size(indexList)//Index List Size
	});
}

void szas::WorldRenderer::Render(const World& world, SwapChain& swapChain, f32 deltaTime)
{	
	////////// ORTHOGRAPHIC CAMERA SET-UP //////////
	auto size = swapChain.GetSize();
	auto aspect = static_cast<f32>(size.width) / size.height;
	auto unitsPerScreenHeight = 5.0f;
	auto viewHeight = unitsPerScreenHeight;
	auto viewWidth = unitsPerScreenHeight * aspect;

	////////// DEVICE CONTEXT //////////
	// - Update the constant buffer before everything
	// - context.UpdateConstantBuffer(vsConstantBuffer, &data);
	// - We want to first clear the buffer, then after rendering on a back buffer, we want to move that back to the front buffer
	// - Record render command that clears content of back buffer and binds it so we can render elements onto it
	// - Use Pipeline
	//	- Bind all objects inside graphics pipeline state (shaders) to actual GPU pipeline
	auto& context = *m_deviceContext;
	context.ClearAndSetBackBuffer(swapChain, {0.251f, 0.141f, 0.31f, 1.0f});
	context.SetGraphicsPipelineState(*m_pipeline);
	context.SetViewportSize(size);

	////////// ACOMPONENTS //////////
	auto numberOfComponents = 0u;
	auto componentList = world.GetAComponents<CubeComponent>(numberOfComponents);

	////////// CONSTANT BUFFER DATA //////////
	ConstantData data{};

	for (auto i : std::views::iota(0u, numberOfComponents))
	{
		auto component = componentList[i];
		auto& transform = component->GetGameObject().GetTransform();

		data =
			ConstantData
			{
				transform.GetWorldMatrix(),
				Matrix4x4::OrthoLH(viewWidth, viewHeight, -10.0f, 10.0f)
			};

		auto& vsConstantBuffer = *m_vsConstantBuffer;
		auto& psConstantBuffer = *m_psConstantBuffer;
		context.UpdateConstantBuffer(vsConstantBuffer, &data);
		//context.UpdateConstantBuffer(psConstantBuffer, &data);

		auto& vb = *m_vertexBuffer;
		auto& ib = *m_indexBuffer;
		context.SetVertexBuffer(vb);
		context.SetConstantBuffer(vsConstantBuffer, psConstantBuffer);
		context.SetIndexBuffer(ib);
		context.Draw4PatchIndexedTriangleList(ib.GetIndexListSize(), 0u, 0u);
	}

	//Pass device context where we will extract the commands from
	m_graphicsDevice.ExecuteCommandList(context);

	//Present our back buffer with its rendered content on the window
	swapChain.Present();

	//Bind the vertex buffer to the graphics pipeline (input assembler stage)
		//First retieve reference to vertex buffer
		//Then call Set Vertex to bind buffer to pipeline
	//Bind constant buffer as well
	//auto& vertexBuffer = *m_vertexBuffer;
	//auto& indexBuffer = *m_indexBuffer;
	//
	//context.SetVertexBuffer(vertexBuffer);
	//context.SetConstantBuffer(vsConstantBuffer, psConstantBuffer);
	//context.SetIndexBuffer(indexBuffer);

	//////////// DRAW TRIANGLES ////////////
		//Can only be called once graphics pipeline is set up. Provides all shaders
		//Set viewport size which defines area of render target (back buffer)
		//Bind vertex buffer to graphics pipeline, which provides vertices from which geometric shapes and raster image will be generated

	// Draws all quads using its own draw function
	//for (size_t i = 0; i < m_quadList.size(); ++i) {
	//	m_quadList[i]->Draw(m_vertexBuffer, context.GetD3D11DeviceContext()); 
	//}
	
	//m_quadList[0]->Draw(m_vertexBuffer, context.GetD3D11DeviceContext());

	//context.DrawQuadList(
	//	vertexBuffer.GetVertexListSize(),		//Vertex List size
	//	0u										//Index we want to start drawing at
	//);
}

szas::WorldRenderer::~WorldRenderer()
{
}
