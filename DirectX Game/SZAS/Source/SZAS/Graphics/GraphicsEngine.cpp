#include <SZAS/Graphics/GraphicsEngine.h>
#include <SZAS/Graphics/GraphicsDevice.h>
#include <SZAS/Graphics/DeviceContext.h>
#include <SZAS/Graphics/SwapChain.h>
#include <SZAS/Graphics/VertexBuffer.h>
#include <SZAS/Math/Vec3.h>

szas::GraphicsEngine::GraphicsEngine(const GraphicsEngineDescriptor& descriptor) : Base(descriptor.base)
{
	m_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDescriptor{ m_logger });

	//Creates the deferred device context
	auto& device = *m_graphicsDevice;
	m_deviceContext = device.CreateDeviceContext();

	//Create a ShaderSourceCode using constexpr (evaluate value at compile time)
	constexpr char shaderSourceCode[] =
		//Row string literal, helps us define a row of strings in one
		R"(
			//Define a semantic. A label that tells the GPU what the label represents and how it should be used in the pipeline
			//Retrieve data from vertex buffer
			float4 VSMain(float3 pos: POSITION): SV_Position
			{
				return float4(pos.xyz, 1.0f);
			}
			//Indicate the output of a pixel shader. Defines final color writes to render target
			//Defines RGBA. This is because render target is back buffer which is in RGBA format
			float4 PSMain(): SV_Target
			{
				return float4(1.0f, 1.0f , 0.0f, 1.0f);
			}
		)";

	constexpr char shaderSourceName[] = "Basic";
	constexpr auto shaderSourceCodeSize = std::size(shaderSourceCode);

	//Call our compile shader method, pass the shader we created
		//VERTEX SHADER
	auto vs = device.CompileShader({
		shaderSourceName,
		shaderSourceCode,
		shaderSourceCodeSize,
		"VSMain",
		ShaderType::VertexShader
	});
	//PIXEL SHADER
	auto ps = device.CompileShader({
		shaderSourceName,
		shaderSourceCode,
		shaderSourceCodeSize,
		"PSMain",
		ShaderType::PixelShader
	});

	//Create Graphics Pipeline State
	m_pipeline = device.CreateGraphicsPipelineState({*vs, *ps});

	//Create vertex list for now
	const Vec3 vertexList[] =
	{
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	//Create Vertex Buffer and store it
	m_vertexBuffer = device.CreateVertexBuffer
	({
		vertexList,					//Vertex List
		std::size(vertexList),		//Vertex List Size
		sizeof(Vec3)				//Vertex Size
	});
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
	context.ClearAndSetBackBuffer(swapChain, {0.529, 0.18, 0.749, 1});
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
