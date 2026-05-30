#include <SZAS/Graphics/GraphicsEngine.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/Graphics/DeviceContext/DeviceContext.h>
#include <SZAS/Graphics/SwapChain/SwapChain.h>
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
	constexpr char shaderFilePath[] = "SZAS/Assets/Shaders/Basic.hlsl";
	//Read the contents of the shader file
	std::ifstream shaderStream(shaderFilePath);
	if (!shaderStream) SZASLogThrowError("Failed to open shader file.");
	//Retrieve file data. So calling Range would call the entire shader into a string
	std::string shaderFileData{
		std::istreambuf_iterator<char>(shaderStream),	//Beginning of the file
		std::istreambuf_iterator<char>()				//Beginning of the end
	};

	//Create a ShaderSourceCode using constexpr (evaluate value at compile time)
	auto shaderSourceCode = shaderFileData.c_str();
	auto shaderSourceCodeSize = shaderFileData.length();

	//Call our compile shader method, pass the shader we created
		//VERTEX SHADER
	auto vs = device.CompileShader({
		shaderFilePath,
		shaderSourceCode,
		shaderSourceCodeSize,
		"VSMain",
		ShaderType::VertexShader
	});
	//PIXEL SHADER
	auto ps = device.CompileShader({
		shaderFilePath,
		shaderSourceCode,
		shaderSourceCodeSize,
		"PSMain",
		ShaderType::PixelShader
	});

	auto vertexShaderSignature = device.CreateVertexShaderSignature({vs});

	//Create Graphics Pipeline State
	m_pipeline = device.CreateGraphicsPipelineState({*vertexShaderSignature, *ps});

	const Vertex vertexList[] =
	{
		//// GREEN RECTANGLE ////
		// Triangle 1 //
			/* V0 */ { {-0.75f, 0.25f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			/* V1 */ { {-0.75f, 0.75f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			/* V2 */ { {-0.25f, 0.25f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
		// Triangle 2 //				
			/* V3 */ { {-0.75f, 0.75f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			/* V4 */ { {-0.25f, 0.75f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			/* V5 */ { {-0.25f, 0.25f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} },
			
		//// RAINBOW TRIANGLE ////
			/* V6 */ { {-0.25f, -0.75f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f}},
			/* V7 */ { {0.0f, 0.5f, 0.0f},    {0.0f, 1.0f, 1.0f, 1.0f} },
			/* V8 */ { {0.25f, -0.75f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },

		//// RAINBOW RECTANGLE ////
			// Triangle 1 //
			/* V8 */  { {0.35f, -0.85f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			/* V9 */  { {0.35f, 0.85f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
			/* V10 */ { {0.85f, -0.85f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
			// Triangle 2
			/* V11 */ { {0.35f, 0.85f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} },
			/* V12 */ { {0.85f, 0.85f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f} },
			/* V13 */ { {0.85f, -0.85f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
	};

	//Create Vertex Buffer and store it
	m_vertexBuffer = device.CreateVertexBuffer
	({
		vertexList,					//Vertex List
		std::size(vertexList),		//Vertex List Size
		sizeof(Vertex)				//Vertex Size
	});

	//Create constant buffer
	//m_constantBuffer = device.CreateConstantBuffer
	//({
	//	{},
	//	sizeof(ConstantData)
	//});
}

szas::GraphicsDevice& szas::GraphicsEngine::GetGraphicsDevice() noexcept
{
	//Using * on a unique pointer gives us a non null reference
	return *m_graphicsDevice;
}

void szas::GraphicsEngine::Render(SwapChain& swapChain)
{
	auto& context = *m_deviceContext;
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
	auto& vertexBuffer = *m_vertexBuffer;
	context.SetVertexBuffer(vertexBuffer);
	
	//////////// DRAW TRIANGLES ////////////
		//Can only be called once graphics pipeline is set up. Provides all shaders
		//Set viewport size which defines area of render target (back buffer)
		//Bind vertex buffer to graphics pipeline, which provides vertices from which geometric shapes and raster image will be generated
	context.DrawTriangleList(
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
