#include "Logging/Logger.h"
#include "Logging/LogMacros.h"

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define DATETIME_STRING_BUFFER_SIZE 20

static const int DATE_YEAR_OFFSET = 1900;
static const int DATE_MONTH_OFFSET = 1;
static const char* const DATETIME_STRING_UNKNOWN = "unknown-datetime";
static const char* const DATETIME_OUTPUT_FORMAT = "%02d-%02d-%04d %02d:%02d:%02d";
static const char* const LOG_OUTPUT_FORMAT_STDOUT = "%s[%s] [%s]%s ";
static const char* const LOG_OUTPUT_FORMAT_STDERR = "%s[%s] [%s] [%s:%d:%s]%s ";

static void Logger_GetCurrentDateTimeString(char* buffer, const size_t buffer_size)
{
    time_t now = time(NULL);
    struct tm local_time;

    if (localtime_s(&local_time, &now) != 0) 
    {
        snprintf(buffer, buffer_size, DATETIME_STRING_UNKNOWN);
        return;
    }

    snprintf
    (
        buffer,
        buffer_size,
        DATETIME_OUTPUT_FORMAT,
        local_time.tm_mday,
        local_time.tm_mon + DATE_MONTH_OFFSET,
        local_time.tm_year + DATE_YEAR_OFFSET,
        local_time.tm_hour,
        local_time.tm_min,
        local_time.tm_sec
    );
}

void Logger_DetailedLog(const LogLevel level, const char* const file_name, const int code_line, const char* const function_name, const char* const format, ...)
{
    if (level != LOG_LEVEL_ONLY && level >= LOG_LEVEL_MIN) return;

    char datetime_buffer[DATETIME_STRING_BUFFER_SIZE];
    Logger_GetCurrentDateTimeString(datetime_buffer, sizeof(datetime_buffer));

    const char* const level_color = LogLevel_GetColor(level);
    const char* const level_name = LogLevel_GetName(level);

    fprintf(stderr, LOG_OUTPUT_FORMAT_STDERR, level_color, datetime_buffer, level_name, file_name, code_line, function_name, LogLevel_GetColor(LOG_LEVEL_DEFAULT));

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    LOG_NEW_LINE();
}

void Logger_StandardLog(const LogLevel level, const char* const format, ...)
{
    if (level != LOG_LEVEL_ONLY && level >= LOG_LEVEL_MIN) return;

    char datetime_buffer[DATETIME_STRING_BUFFER_SIZE];
    Logger_GetCurrentDateTimeString(datetime_buffer, sizeof(datetime_buffer));

    const char* const level_color = LogLevel_GetColor(level);
    const char* const level_name = LogLevel_GetName(level);

    fprintf(stdout, LOG_OUTPUT_FORMAT_STDOUT, level_color, datetime_buffer, level_name, LogLevel_GetColor(LOG_LEVEL_DEFAULT));

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);

    LOG_NEW_LINE();
}