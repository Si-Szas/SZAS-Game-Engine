#include <SZAS/Game/WorldRenderer.h>
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
#include <SZAS/AComponent/SphereComponent.h>
#include <SZAS/AComponent/CameraComponent.h>

#include <SZAS/Math/Vec2.h>
#include <SZAS/Math/Vec3.h>
#include <fstream>
#include <ranges>
#include <DirectXMath.h>

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

	auto vertexShaderSignature = device.CreateVertexShaderSignature({ vs });

	//Create Graphics Pipeline State
	m_pipeline = device.CreateGraphicsPipelineState({ *vertexShaderSignature, *ps, *hs, *ds });

	////////////// CREATING QUADS //////////////
	//const Vertex quad1Vertices[] =
	//{
	//	/* BL */ { {-0.95f, 0.15f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} },
	//	/* TL */ { {-0.95f, 0.85f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f} },
	//	/* BR */ { {-0.40f, 0.15f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f} },
	//	/* TP */ { {-0.40f, 0.85f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f} }
	//};

	/// CREATING A 3D OBJECT //
	//Defines how smooth the circle looks
	int radius = 1;
	int sliceCount = radius * 20;
	int stackCount = radius * 20;

	std::vector<Vertex> sphereVertices;
	sphereVertices.push_back(Vertex({ 0.0f, szas::f32(radius), 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }));

	float phiStep = DirectX::XM_PI / stackCount;
	float thetaStep = DirectX::XM_2PI / sliceCount;

	for (int i = 1; i < stackCount; ++i) {
		float phi = i * phiStep;
		for (int j = 0; j <= sliceCount; ++j) {
			f32 theta = j * thetaStep;

			Vertex v;

			// 1. Compute your float positions explicitly first
			v.position.x = radius * sinf(phi) * cosf(theta);
			v.position.y = radius * cosf(phi);
			v.position.z = radius * sinf(phi) * sinf(theta);

			// 2. Compute your float colors explicitly first
			v.color.x = (v.position.x / radius) * 0.5f + 0.5f;
			v.color.y = (v.position.y / radius) * 0.5f + 0.5f;
			v.color.z = (v.position.z / radius) * 0.5f + 0.5f;
			v.color.w = 1.0f;

			const Vertex* vertexArray = static_cast<const Vertex*>(&v);
			//allQuadVertices.push_back(vertexArray[k]);

			sphereVertices.push_back(*vertexArray);
		}
	}

	sphereVertices.push_back(Vertex({ 0.0f, szas::f32(-radius), 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0f }));

	std::vector<ui32> sphereIndices;
	for (int i = 0; i < stackCount; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			sphereIndices.push_back(0); // Top pole (degenerated edge)
			sphereIndices.push_back(0); // Top pole (degenerated edge)
			sphereIndices.push_back(static_cast<uint32_t>(1 + j));
			sphereIndices.push_back(static_cast<uint32_t>(1 + j + 1));
		}
	}
	//for (uint32_t i = 1; i <= sliceCount; ++i) {
	//	sphereIndices.push_back(0);
	//	sphereIndices.push_back(i + 1);
	//	sphereIndices.push_back(i);
	//}

	// Inner ring quads
	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;
	for (int i = 0; i < stackCount - 2; ++i) {
		for (int j = 0; j < sliceCount; ++j) {
			// Calculate the 4 unique quad corner vertices cleanly
			uint32_t topLeft = static_cast<uint32_t>(baseIndex + i * ringVertexCount + j);
			uint32_t topRight = static_cast<uint32_t>(baseIndex + i * ringVertexCount + j + 1);
			uint32_t bottomLeft = static_cast<uint32_t>(baseIndex + (i + 1) * ringVertexCount + j);
			uint32_t bottomRight = static_cast<uint32_t>(baseIndex + (i + 1) * ringVertexCount + j + 1);

			// Push exactly 4 indices per patch in Clockwise (CW) winding order
			sphereIndices.push_back(topLeft);
			sphereIndices.push_back(topRight);
			sphereIndices.push_back(bottomLeft);
			sphereIndices.push_back(bottomRight);
		}
	}

	//for (int i = 0; i < stackCount - 2; ++i) {
	//	for (int j = 0; j < sliceCount; ++j) {
	//		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + i * ringVertexCount + j));
	//		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + i * ringVertexCount + j + 1));
	//		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + (i + 1) * ringVertexCount + j));
	//		
	//		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + (i + 1) * ringVertexCount + j));
	//		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + i * ringVertexCount + j + 1));
	//		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + (i + 1) * ringVertexCount + j + 1));
	//	}
	//}
	
	// Bottom pole triangles
	uint32_t southPoleIndex = (uint32_t)sphereVertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	//for (uint32_t i = 0; i < sliceCount; ++i) {
	//	sphereIndices.push_back(southPoleIndex);
	//	sphereIndices.push_back(baseIndex + i);
	//	sphereIndices.push_back(baseIndex + i + 1);
	//}
	for (int j = 0; j < sliceCount; ++j) {
		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + j));
		sphereIndices.push_back(static_cast<uint32_t>(baseIndex + j + 1));
		sphereIndices.push_back(southPoleIndex); // Bottom pole (degenerated edge)
		sphereIndices.push_back(southPoleIndex); // Bottom pole (degenerated edge)
	}

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

	//m_cubeVertexBuffer = device.CreateVertexBuffer
	//({
	//	cubeVertices,
	//	std::size(cubeVertices),
	//	sizeof(Vertex)
	//});

	m_vertexBuffer.push_back(device.CreateVertexBuffer
	({
		sphereVertices.data(),					//Vertex List
		static_cast<UINT>(sphereVertices.size()),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
	}));

	m_vertexBuffer.push_back(device.CreateVertexBuffer
	({
		cubeVertices,
		std::size(cubeVertices),
		sizeof(Vertex)
	}));

	//Create constant buffer
	m_dsConstantBuffer = device.CreateConstantBuffer
	({
		&m_dsConstantBuffer,
		sizeof(ConstantData)
	});

	//We don't have any constant data to pass to the vertex, hull, or pixel shader
	m_vsConstantBuffer = nullptr;
	m_hsConstantBuffer = nullptr;
	m_psConstantBuffer = nullptr;

	m_indexBuffer.push_back(device.CreateIndexBuffer
	({
		sphereIndices.data(),//Index List
		static_cast<UINT>(sphereIndices.size())//Index List Size
	}));

	m_indexBuffer.push_back(device.CreateIndexBuffer
	({
		indexList,//Index List
		std::size(indexList)//Index List Size
	}));
}

void szas::WorldRenderer::Render(const World& world, SwapChain& swapChain, f32 deltaTime)
{	
	////////// ORTHOGRAPHIC CAMERA SET-UP //////////
	auto size = swapChain.GetSize();
	
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
	
	////////// CONSTANT BUFFER DATA //////////
	ConstantData data{};
	{
		auto cameraComponents = world.GetAComponents<CameraComponent>(numberOfComponents);

		for (auto i : std::views::iota(0u, numberOfComponents))
		{
			auto camComponent = cameraComponents[i];
			data.view = camComponent->GetViewMatrix();
			camComponent->SetViewportSize(size);
			data.projection = camComponent->GetProjectionMatrix();
			break;
		}
	}

	{
		auto cubeComponents = world.GetAComponents<CubeComponent>(numberOfComponents);

		for (auto i : std::views::iota(0u, numberOfComponents))
		{
			auto cubeComponent = cubeComponents[i];
			auto& transform = cubeComponent->GetGameObject().GetTransform();

			data.world = transform.GetAffineWorldMatrix();

			////////// UPDATE EACH CONSTANT BUFFER PASSED TO THE SHADERS //////////
			auto& vsConstantBuffer = *m_vsConstantBuffer;
			auto& hsConstantBuffer = *m_hsConstantBuffer;
			auto& dsConstantBuffer = *m_dsConstantBuffer;
			auto& psConstantBuffer = *m_psConstantBuffer;
			context.UpdateConstantBuffer(vsConstantBuffer, &data);
			context.UpdateConstantBuffer(hsConstantBuffer, &data);
			context.UpdateConstantBuffer(dsConstantBuffer, &data);
			context.UpdateConstantBuffer(psConstantBuffer, &data);
			
			auto& vb = *m_vertexBuffer[1];
			auto& ib = *m_indexBuffer[1];
			context.SetVertexBuffer(vb);
			////////// SET EACH CONSTANT BUFFER PASSED TO THE SHADERS //////////
			context.SetVSConstantBuffer(0, 1, vsConstantBuffer);
			context.SetHSConstantBuffer(0, 1, hsConstantBuffer);
			context.SetDSConstantBuffer(0, 1, dsConstantBuffer);
			context.SetPSConstantBuffer(0, 1, psConstantBuffer);
			
			context.SetIndexBuffer(ib);
			context.Draw3PatchIndexedTriangleList(ib.GetIndexListSize(), 0u, 0u);
		}
	}
	

	//Pass device context where we will extract the commands from
	m_graphicsDevice.ExecuteCommandList(context);

	//Present our back buffer with its rendered content on the window
	swapChain.Present();
}

szas::WorldRenderer::~WorldRenderer()
{
}
