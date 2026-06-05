#include <SZAS/Game/Game.h>
#include <SZAS/Window/Window.h>
#include <SZAS/Graphics/GraphicsEngine.h>
#include "SZAS/Core/Logger.h"
#include <SZAS/Game/Display.h>

szas::Game::Game(const GameDescriptor& descriptor)
{
	m_logger = std::make_unique<Logger>(descriptor.logLevel);

	SZASLogInformation("| Szas | DirectX C++ Game Engine |");
	SZASLogInformation("|--------------------------------|\n");

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDescriptor{ *m_logger });
	m_display = std::make_unique<Display>(DisplayDescriptor{ {*m_logger, descriptor.windowSize}, m_graphicsEngine->GetGraphicsDevice()});

	SZASLogInformation("Game successfully initialized.");
}

szas::Game::~Game()
{
	SZASLogInformation("Game is shutting down...");
}

void szas::Game::OnInternalUpdate()
{
	m_graphicsEngine->Render(m_display->GetSwapChain());
}

szas::Logger& szas::Game::GetLogger() noexcept
{
	return *m_logger;
}