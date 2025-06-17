#include "ByteForgeEngine.h"

#include "ByteForgeEngine/Application/EngineApplication.h"
#include "ByteForgeEngine/Application/EngineApplicationPresenter.h"

#include <ByteForgeLogging.h>

bool ByteForgeEngine_Start(const int argc, const char** argv)
{
	if (!MemoryUsageReport_Init()) return false;

	EngineApplication* engine_application;

	if (!EngineApplication_Create(argc, argv, &engine_application))
	{
		LOG_FATAL("Error when trying to create Engine Application instance.");
		return false;
	}

	EngineApplicationPresenter_ShowIntroductionMessage(engine_application->arguments);

	if (!EngineApplication_Initialize(engine_application))
	{
		LOG_FATAL("Error when trying to initialize Engine Application");
		return false;
	}

	EngineApplication_Run(engine_application);

	EngineApplication_Free(&engine_application);
	
	EngineApplicationPresenter_ShowExitMessage();

	return true;
}