#include "Logging/LogLevel.h"
#include "Logging/LogStyles.h"

static const char* const LOG_LEVEL_COLORS[] = 
{
    [ LOG_LEVEL_FATAL ]   = LOG_STYLE_BOLD LOG_STYLE_WHITE_TEXT LOG_STYLE_RED_BACKGROUND,
    [ LOG_LEVEL_ERROR ]   = LOG_STYLE_BOLD LOG_STYLE_RED_TEXT,
    [ LOG_LEVEL_WARNING ] = LOG_STYLE_BOLD LOG_STYLE_YELLOW_TEXT,
    [ LOG_LEVEL_SUCCESS ] = LOG_STYLE_BOLD LOG_STYLE_GREEN_TEXT,
    [ LOG_LEVEL_DEBUG ]   = LOG_STYLE_WHITE_TEXT,
    [ LOG_LEVEL_TRACE ]   = LOG_STYLE_WHITE_TEXT,
    [ LOG_LEVEL_INFO ]    = LOG_STYLE_CYAN_TEXT,
    [ LOG_LEVEL_DEFAULT ] = LOG_STYLE_RESET
};

static const char* const LOG_LEVEL_NAMES[] = 
{
    [ LOG_LEVEL_FATAL ]   = "FATAL",
    [ LOG_LEVEL_ERROR ]   = "ERROR",
    [ LOG_LEVEL_WARNING ] = "WARNING",
    [ LOG_LEVEL_SUCCESS ] = "SUCCESS",
    [ LOG_LEVEL_DEBUG ]   = "DEBUG",
    [ LOG_LEVEL_TRACE ]   = "TRACE",
    [ LOG_LEVEL_INFO ]    = "INFO",
    [ LOG_LEVEL_DEFAULT ] = "DEFAULT"
};

const char* const LogLevel_GetColor(const LogLevel log_level)
{
    if (log_level >= 0 && log_level < LOG_LEVEL_COUNT)
    {
        return LOG_LEVEL_COLORS[log_level];
    }

    return LOG_STYLE_RESET;
}

const char* const LogLevel_GetName(const LogLevel log_level)
{
    if (log_level >= 0 && log_level < LOG_LEVEL_COUNT)
    {
        return LOG_LEVEL_NAMES[log_level];
    }

    return LOG_LEVEL_NAMES[LOG_LEVEL_DEFAULT];
}