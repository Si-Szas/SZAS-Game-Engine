#include <SZAS/Graphics/SwapChain.h>

szas::SwapChain::SwapChain(const SwapChainDescriptor& swapChainDescriptor, const GraphicsResourceDescriptor& graphicsResourceDescriptor):
	GraphicsResource(graphicsResourceDescriptor)
{
	DXGI_SWAP_CHAIN_DESC dxgiDescriptor{};

	//Define attributes of buffers used by swap chain
	//Canvas where graphics will be rendered
	dxgiDescriptor.BufferDesc.Width = std::max(1, swapChainDescriptor.windowSize.width);
	dxgiDescriptor.BufferDesc.Height = std::max(1, swapChainDescriptor.windowSize.height);
	//UNORM means normalized, unsigned integers
	dxgiDescriptor.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//How many backbuffers
	//If swap chain is in windowed mode, only 2 back buffers (front not included), if fullscreen, then has 3 back buffers
	dxgiDescriptor.BufferCount = 2;
	//Tells DXGI that we'll use the buffer as our render target
	dxgiDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	dxgiDescriptor.OutputWindow = static_cast<HWND>(swapChainDescriptor.windowHandle);
	//Set sample counter for multi sample anti-aliasing
	dxgiDescriptor.SampleDesc.Count = 1;
	//Back buffer is not copied to a separate surface
	//Back buffers created in swap chain is shared with the DWM
	dxgiDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiDescriptor.Windowed = TRUE;

	//Fails if we pass 0 negative values for the width or the height, which is why we use the standard max function
	SZASGraphicsLogErrorAndThrow(m_dxgiFactory.CreateSwapChain
	(
		&m_d3dDevice,		//Pass device, type IUknown, since it can accept multiple types of devices
		&dxgiDescriptor,	//Address of swap chain descriptor
		&m_swapChain //Retrieve output parameter, dxgi swapp chain
	),
		"CreateSwapChain() failed.");
}
