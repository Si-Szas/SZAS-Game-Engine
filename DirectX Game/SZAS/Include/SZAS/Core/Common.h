#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Logger.h>
#include <SZAS/Math/Rect.h>

namespace szas 
{
	//Groups all dependencies used by Base Class
	struct BaseDescriptor
	{
		Logger& logger;
	};

	struct WindowDescriptor
	{
		BaseDescriptor base;
		Rect size{};
	};

	struct DisplayDescriptor
	{
		WindowDescriptor window;
		GraphicsDevice& graphicsDevice;
	};

	struct GraphicsEngineDescriptor 
	{
		BaseDescriptor base;
	};

	struct GraphicsDeviceDescriptor
	{
		BaseDescriptor base;
	};

	struct SwapChainDescriptor
	{
		void* windowHandle{};
		Rect windowSize{};
	};

	struct GameDescriptor
	{
		Rect windowSize{ 1280, 720 };
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};
}