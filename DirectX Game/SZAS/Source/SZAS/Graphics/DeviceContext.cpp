#include <SZAS/Graphics/DeviceContext.h>
#include <SZAS/Graphics/SwapChain.h>

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
