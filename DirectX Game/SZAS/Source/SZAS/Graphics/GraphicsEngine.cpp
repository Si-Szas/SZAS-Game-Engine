#include <SZAS/Graphics/GraphicsEngine.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/Graphics/DeviceContext/DeviceContext.h>
#include <SZAS/Graphics/SwapChain/SwapChain.h>
#include <SZAS/Time/EngineTime.h>
#include <SZAS/Graphics/VertexBuffer/VertexBuffer.h>
#include <SZAS/Graphics/ConstantBuffer/ConstantBuffer.h>
#include <SZAS/Math/Vec3.h>
#include <fstream>

szas::GraphicsEngine::GraphicsEngine(const GraphicsEngineDescriptor& descriptor) : Base(descriptor.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDescriptor{ m_logger });

	//Creates the deferred device context
	auto& device = *m_graphicsDevice;
	m_deviceContext = device.CreateDeviceContext();

	//Define the Shader File Path
		// Relative paths are relative to the root of project folder (DirectX Game Folder)
	constexpr char vertexShaderFilePath[] = "SZAS/Assets/Shaders/Wireframe/WireframeVertexShader.hlsl";
	//Read the contents of the shader file
	std::ifstream vertexShaderStream(vertexShaderFilePath);
	if (!vertexShaderStream) SZASLogThrowError("Failed to open WireframeVertexShader.hlsl file.");
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
	constexpr char hullShaderFilePath[] = "SZAS/Assets/Shaders/Wireframe/WireframeHullShader.hlsl";
	std::ifstream hullShaderStream(hullShaderFilePath);
	if (!hullShaderStream) SZASLogThrowError("Failed to open WireframeHullShader.hlsl file.");

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
	constexpr char domainShaderFilePath[] = "SZAS/Assets/Shaders/Wireframe/WireframeDomainShader.hlsl";
	std::ifstream domainShaderStream(domainShaderFilePath);
	if (!domainShaderStream) SZASLogThrowError("Failed to open WireframeDomainShader.hlsl file.");

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

	constexpr char pixelShaderFilePath[] = "SZAS/Assets/Shaders/Wireframe/WireframePixelShader.hlsl";
	//Read the contents of the shader file
	std::ifstream pixelShaderStream(pixelShaderFilePath);
	if (!pixelShaderStream) SZASLogThrowError("Failed to open WireframePixelShader.hlsl file.");
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

	//TESTING WIREFRAME SHADER
	const Vertex vertexList[] =
	{
		//1ST TRIANGLE
		/* V0 */{ {-0.5f, -0.5f, 0.0f}, {1.0f,0.0f,0.0f,1.0f} },
		/* V1 */{ {-0.5f, 0.5f, 0.0f},	{0.0f,1.0f,0.0f,1.0f} },
		/* V2 */{ {0.5f, 0.5f, 0.0f},	{0.0f,0.0f,1.0f,1.0f} },

		/* V3 */{ {0.5f, 0.5f, 0.0f},	{0.0f,0.0f,1.0f,1.0f} },
		/* V4 */{ {0.5f, -0.5f, 0.0f},	{0.0f,1.0f,0.0f,1.0f} },
		/* V5 */{ {-0.5f, -0.5f, 0.0f}, {1.0f,0.0f,0.0f,1.0f} },
	};

	//Create Vertex Buffer and store it
	m_vertexBuffer = device.CreateVertexBuffer
	({
		vertexList,					//Vertex List
		std::size(vertexList),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
	});

	//Create constant buffer
	m_constantBuffer = device.CreateConstantBuffer
	({
		&m_constantBuffer,
		sizeof(ConstantData)
	});
}

szas::GraphicsDevice& szas::GraphicsEngine::GetGraphicsDevice() noexcept
{
	//Using * on a unique pointer gives us a non null reference
	return *m_graphicsDevice;
}

void szas::GraphicsEngine::Render(SwapChain& swapChain)
{
	auto& constantBuffer = *m_constantBuffer;
	auto& context = *m_deviceContext;
	d64 deltaTime = szas::EngineTime::GetDeltaTime();

	m_position += deltaTime * 0.25f;
	m_rotation += deltaTime * 2.0f;
	m_scale = std::abs(std::sin(m_rotation));
	
	//SZASLogInformation("Pos: X:{} Y:{}", m_position, m_position);
	//SZASLogInformation("Rot: Z:{}", m_rotation);
	//SZASLogInformation("Scale: {}", m_scale);

	auto worldMatrix =
		Mat4x4::rotateAlongZ(m_rotation) *
		Mat4x4::scale({m_scale, m_scale, m_scale}) *
		Mat4x4::translate({ m_position ,m_position ,0 });

	ConstantData data
	{
		/*World Matrix*/	worldMatrix,
		/*Fill Color*/		{0.0f, 0.0f, 0.0f, 0.0f},
		/*Mesh Color*/		{1.0f, 0.0f, 1.0f, 0.0f},
		/*Line Thickness*/	5.0f
	};

	//Update the constant buffer before everything
	context.UpdateConstantBuffer(constantBuffer, &data);
	//We want to first clear the buffer, then after rendering on a back buffer, we want to move that back to the front buffer
	context.ClearAndSetBackBuffer(swapChain, {0.251f, 0.141f, 0.31f, 1.0f});
	//Record render command that clears content of back buffer and binds it so we can render elements onto it
	
	//Use Pipeline
		//Bind all objects inside graphics pipeline state (shaders) to actual GPU pipeline
	context.SetGraphicsPipelineState(*m_pipeline);

	//Call set viewport size method and retrieve size from swap chain
	context.SetViewportSize(swapChain.GetSize());

	//Bind the vertex buffer to the graphics pipeline (input assembler stage)
		//First retieve reference to vertex buffer
		//Then call Set Vertex to bind buffer to pipeline
	//Bind constant buffer as well
	auto& vertexBuffer = *m_vertexBuffer;
	context.SetVertexBuffer(vertexBuffer);
	context.SetConstantBuffer(constantBuffer);

	//////////// DRAW TRIANGLES ////////////
		//Can only be called once graphics pipeline is set up. Provides all shaders
		//Set viewport size which defines area of render target (back buffer)
		//Bind vertex buffer to graphics pipeline, which provides vertices from which geometric shapes and raster image will be generated
	context.DrawTriangleListWithTessellation(
		vertexBuffer.GetVertexListSize(),		//Vertex List size
		0u										//Index we want to start drawing at
	);

	//Allow the GPU to execute the list of commands recorded by the device context in order to finally render something to the back buffer
	auto& device = *m_graphicsDevice;
	//Pass device context where we will extract the commands from
	device.ExecuteCommandList(context);

	//Present our back buffer with its rendered content on the window
	swapChain.Present();
}

szas::GraphicsEngine::~GraphicsEngine()
{
}
