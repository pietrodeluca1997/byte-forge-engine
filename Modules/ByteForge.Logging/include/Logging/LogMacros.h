#pragma once

#include "Logger.h"

#include <stdio.h>
#include <string.h>

#define LOG_LEVEL_ONLY -1
#define LOG_LEVEL_MIN LOG_LEVEL_WARNING

/**
 * @brief Macro to extract the file name from a full file path.
 *
 * If the file path contains backslashes (`\`), this macro extracts only the file name.
 * If no backslash is present, it returns the full file path.
 */
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

/**
* @brief Macro to log a fatal error message with file, line, and function information.
*/
#define LOG_FATAL(format, ...)   Logger_DetailedLog(LOG_LEVEL_FATAL, __FILENAME__, __LINE__, __func__, format, ##__VA_ARGS__)

/**
* @brief Macro to log an error message with file, line, and function information.
*/
#define LOG_ERROR(format, ...)   Logger_DetailedLog(LOG_LEVEL_ERROR, __FILENAME__, __LINE__, __func__, format, ##__VA_ARGS__)

/**
* @brief Macro to log a warning message with file, line, and function information.
*/
#define LOG_WARNING(format, ...) Logger_DetailedLog(LOG_LEVEL_WARNING, __FILENAME__, __LINE__, __func__, format, ##__VA_ARGS__)

/**
* @brief Macro to log a success message.
*/
#define LOG_SUCCESS(format, ...) Logger_StandardLog(LOG_LEVEL_SUCCESS, format, ##__VA_ARGS__)

/**
* @brief Macro to log a debug message.
*/
#define LOG_DEBUG(format, ...)   Logger_StandardLog(LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)

/**
* @brief Macro to log a trace message.
*/
#define LOG_TRACE(format, ...)   Logger_DetailedLog(LOG_LEVEL_TRACE, __FILENAME__, __LINE__, __func__, format, ##__VA_ARGS__)

/**
* @brief Macro to log an informational message.
*/
#define LOG_INFO(format, ...)    Logger_StandardLog(LOG_LEVEL_INFO, format, ##__VA_ARGS__)

/**
* @brief Macro to output a new line character.
*/
#define LOG_NEW_LINE()           putchar('\n')