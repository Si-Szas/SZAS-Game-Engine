#include <SZAS/Time/EngineTime.h>
#include <SZAS/Core/Logger.h>

szas::EngineTime* szas::EngineTime::sharedInstance = nullptr;

void szas::EngineTime::Initialize()
{
	sharedInstance = new EngineTime();
}

szas::EngineTime::EngineTime()
{
}

void szas::EngineTime::LogFrameStart()
{
	//if (!sharedInstance) sharedInstance = new EngineTime();

	sharedInstance->timeStart = std::chrono::system_clock::now();
}

void szas::EngineTime::LogFrameEnd()
{
	//if (!sharedInstance) sharedInstance = new EngineTime();

	sharedInstance->timeEnd = std::chrono::system_clock::now();
	std::chrono::duration<d64> elapsedSeconds = sharedInstance->timeEnd - sharedInstance->timeStart;

	sharedInstance->deltaTime = elapsedSeconds.count();

	std::cout << "Frame update finished in: " << sharedInstance->deltaTime << " seconds\n";
}

szas::d64 szas::EngineTime::GetDeltaTime()
{
	return sharedInstance->deltaTime;
}

szas::EngineTime::~EngineTime()
{
}
