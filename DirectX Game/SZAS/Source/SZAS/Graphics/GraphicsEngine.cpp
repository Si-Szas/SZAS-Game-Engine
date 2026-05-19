#include <SZAS/Graphics/GraphicsEngine.h>
#include <SZAS/Graphics/GraphicsDevice.h>
#include <SZAS/Graphics/DeviceContext.h>
#include <SZAS/Graphics/SwapChain.h>

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
			void VSMain()
			{
			}
	
			void PSMain()
			{
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
