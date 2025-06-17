#include "ByteForgeEngine/Application/EngineApplicationPresenter.h"

#include <ByteForgeLogging.h>

void EngineApplicationPresenter_ShowIntroductionMessage(const EngineApplicationArguments* const arguments)
{
    LOG_INFO("=============================================");
    LOG_INFO("      Welcome to the Byte Forge Engine!      ");
    LOG_INFO("=============================================");
    LOG_NEW_LINE();

    LOG_INFO("Engine initiated with %d argument(s):", arguments->count);

    for (int i = 0; i < arguments->count; i++)
    {
        LOG_INFO("\t - Argument [%d]: %s", i, arguments->values[i]);
    }

    LOG_NEW_LINE();
}

void EngineApplicationPresenter_ShowExitMessage()
{
    LOG_NEW_LINE();
    LOG_SUCCESS("Engine application terminated successfully.");
    LOG_NEW_LINE();
    LOG_SUCCESS("=============================================");
    LOG_SUCCESS("   Thank you for trying Byte Forge Engine!   ");
    LOG_SUCCESS("=============================================");
    LOG_NEW_LINE();
}