#include <SZAS/Game/Game.h>
#include <SZAS/Window/Window.h>
#include <SZAS/Graphics/GraphicsDevice/GraphicsDevice.h>
#include <SZAS/Core/Logger.h>
#include <SZAS/Game/Display.h>
#include <SZAS/Game/World.h>
#include <SZAS/Game/WorldRenderer.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/InputSystem/InputSystem.h>

szas::Game::Game(const GameDescriptor& descriptor)
{
	m_logger = std::make_unique<Logger>(descriptor.logLevel);

	SZASLogInformation("| Szas | DirectX C++ Game Engine |");
	SZASLogInformation("|--------------------------------|\n");

	//Since input system needs world and world needs input system, we just set it as null for now then initialize later
	m_inputSystem = std::make_unique<InputSystem>(InputSystemDescriptor{ { *m_logger }, {nullptr} });
	m_graphicsDevice = std::make_unique<GraphicsDevice>(GraphicsDeviceDescriptor{ *m_logger });
	m_display = std::make_unique<Display>(DisplayDescriptor{ {*m_logger, descriptor.windowSize}, *m_graphicsDevice });
	m_worldRenderer = std::make_unique<WorldRenderer>(WorldRendererDescriptor{ {*m_logger}, *m_graphicsDevice });
	//Initialize world
	m_world = std::make_unique<World>(WorldDescriptor{ BaseDescriptor{*m_logger}, GameContext{*m_inputSystem}, {*m_worldRenderer} });
	//Set world in input system to be initialized since it was passed as null at first
	m_inputSystem->SetWorld(*m_world);

	//TEMPORARY CURSOR LOCK
	m_inputSystem->SetCursorLockArea(m_display->GetClientAreaInScreenSpace());

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(static_cast<HWND>(m_display->GetHandle()));
	ImGui_ImplDX11_Init(
		m_graphicsDevice.get()->GetD3DDevice().Get(), 
		m_graphicsDevice.get()->GetD3DDeviceContext().Get()
	);
	ImGui::StyleColorsDark();
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	SZASLogInformation("Game successfully initialized.");
}

szas::Game::~Game()
{
	//For proper clean up, including IMGUI
	if (ImGui::GetCurrentContext() != nullptr)
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	SZASLogInformation("Game is shutting down...");
}

void szas::Game::OnInternalUpdate(f32 deltaTime)
{
	m_inputSystem->Update();

	OnUpdate(deltaTime);
	m_world->Update(deltaTime);
	m_worldRenderer->Render(*m_world, m_display->GetSwapChain(), deltaTime);
}

szas::Logger& szas::Game::GetLogger() noexcept
{
	return *m_logger;
}

szas::InputSystem& szas::Game::GetInputSystem() noexcept
{
	return *m_inputSystem;
}

szas::World& szas::Game::GetWorld() noexcept
{
	return *m_world;
}
