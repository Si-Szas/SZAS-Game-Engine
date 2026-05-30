#include <SZAS/Game/Game.h>
#include <SZAS/Window/Window.h>
#include <SZAS/Graphics/GraphicsEngine.h>
#include "SZAS/Core/Logger.h"
#include <SZAS/Game/Display.h>

szas::Game::Game(const GameDescriptor& descriptor) :
	Base({*std::make_unique<Logger>(descriptor.logLevel).release()}),
	m_loggerPtr(&m_logger)
{
	SZASLogInformation("| Szas | DirectX C++ Game Engine |");
	SZASLogInformation("|--------------------------------|\n");

	m_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDescriptor{ m_logger });
	m_display = std::make_unique<Display>(DisplayDescriptor{ {m_logger, descriptor.windowSize}, m_graphicsEngine->GetGraphicsDevice()});

	SZASLogInformation("Game successfully initialized.");
}

szas::Game::~Game()
{
	SZASLogInformation("Game is shutting down...");
}

void szas::Game::OnInternalUpdate()
{
	//Delta time stuff is here...

	m_graphicsEngine->Render(m_display->GetSwapChain());
}
