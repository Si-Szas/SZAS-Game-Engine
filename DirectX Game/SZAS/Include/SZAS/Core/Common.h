#pragma once
#include <SZAS/Core/Core.h>
#include <SZAS/Core/Logger.h>

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
	};

	struct GraphicsEngineDescriptor 
	{
		BaseDescriptor base;
	};

	struct RenderSystemDescriptor
	{
		BaseDescriptor base;
	};

	struct GameDescriptor
	{
		Logger::LogLevel logLevel = Logger::LogLevel::Error;
	};
}