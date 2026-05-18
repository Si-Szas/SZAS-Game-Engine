#include <SZAS/Game/Display.h>
#include <SZAS/Graphics/GraphicsDevice.h>

szas::Display::Display(const DisplayDescriptor& descriptor): Window(descriptor.window)
{
	m_swapChain = descriptor.graphicsDevice.CreateSwapChain({m_handle, m_size});
}

szas::SwapChain& szas::Display::GetSwapChain() noexcept
{
	return *m_swapChain;
}
