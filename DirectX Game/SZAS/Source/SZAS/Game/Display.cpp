#include <SZAS/Game/Display.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>

#include <SZAS/Graphics/ImGui/imgui_impl_dx11.h>
#include <SZAS/Graphics/ImGui/imgui_impl_win32.h>

szas::Display::Display(const DisplayDescriptor& descriptor): Window(descriptor.window)
{
	m_swapChain = descriptor.graphicsDevice.CreateSwapChain({m_handle, m_size});

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(m_handle);
	ImGui_ImplDX11_Init(descriptor.graphicsDevice.GetD3DDevice().Get(), descriptor.graphicsDevice.GetD3DDeviceContext().Get());
	ImGui::StyleColorsDark();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	//Enable docking
}

szas::SwapChain& szas::Display::GetSwapChain() noexcept
{
	return *m_swapChain;
}
