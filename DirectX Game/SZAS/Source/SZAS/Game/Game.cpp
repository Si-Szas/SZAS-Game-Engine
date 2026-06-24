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

	SZASLogInformation("Game successfully initialized.");
}

szas::Game::~Game()
{
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
