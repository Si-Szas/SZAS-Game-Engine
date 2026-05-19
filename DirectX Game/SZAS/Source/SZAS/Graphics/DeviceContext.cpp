#include <SZAS/Graphics/DeviceContext.h>
#include <SZAS/Graphics/SwapChain.h>
#include <SZAS/Graphics/GraphicsPipelineState.h>

szas::DeviceContext::DeviceContext(const GraphicsResourceDescriptor& descriptor) :
	GraphicsResource(descriptor)
{
	SZASGraphicsLogThrowOnFail(
	m_d3dDevice.CreateDeferredContext(
		0,		//Reserved parameter that doesn't affect deferred context
		&m_context	//Output parameter where we receive D311 Device instance
	), "CreateDeferredContext() failed.");
}

void szas::DeviceContext::ClearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	//Clear the content of the render target view
	//Clear and fill back buffer with a specific color

	//Should be in a range of 0 to 1
	f32 colorArray[] = {color.x, color.y, color.z, color.w};
	
	auto RTV = swapChain.m_renderTargetView.Get();

	m_context->ClearRenderTargetView(
		RTV,	//RTV, object representing view into a so-called render target
		colorArray							//Array of 4 float values representing RGBA	
	);
	
	//Call OMSetRenderTarget to bind buffer we want to render graphics into
	m_context->OMSetRenderTargets(
		1,			//Number of render target views (we set all in one view, our back buffer)
		&RTV,		//An array of pointers to the views (we simulate an array using &)
		nullptr		//Depth Stensive View
	);
}

void szas::DeviceContext::SetGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
	//Actually binds vertex shader to GPU pipeline (use this vertex shader for the next draw calls)
	//It's like in GDGRAP1 where you had to call what shader you wanted to use before drawing specific things
	m_context->VSSetShader(
		pipeline.m_vertexShader.Get(),	//Get the Vertex Shader in Pipeline
		nullptr,						//Related to dynamic shader linkage
		0								//Related to dynamic shader linkage
	);

	//Do the same but for pixel shader
	m_context->PSSetShader(
		pipeline.m_pixelShader.Get(),	//Get Pixel Shader in Pipeline
		nullptr,
		0
	);
}
