#include <SZAS/Game/Display.h>
#include <SZAS/Graphics/RenderSystem.h>

szas::Display::Display(const DisplayDescriptor& descriptor): Window(descriptor.window)
{
	m_swapChain = descriptor.renderSystem.createSwapChain({m_handle, m_size});
}
