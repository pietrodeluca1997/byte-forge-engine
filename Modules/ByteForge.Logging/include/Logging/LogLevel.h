#pragma once

/**
 * @brief Enum representing different log levels.
 *
 * The log levels are ordered from the most critical (fatal) to the least critical (info).
 */
typedef enum
{
    LOG_LEVEL_INFO = 0,
    LOG_LEVEL_DEBUG = 1,
    LOG_LEVEL_TRACE = 2,
    LOG_LEVEL_SUCCESS = 3,
    LOG_LEVEL_WARNING = 4,
    LOG_LEVEL_ERROR = 5,
    LOG_LEVEL_FATAL = 6,
    LOG_LEVEL_DEFAULT = 7,
    LOG_LEVEL_COUNT = 8
} LogLevel;

/**
 * @brief Array of color codes associated with each log level.
 *
 * The colors are used to distinguish the log levels visually in the terminal.
 */
extern const char* const LOG_LEVEL_COLORS[LOG_LEVEL_COUNT];

/**
 * @brief Returns the color associated with a given log level.
 *
 * @param level: The log level for which the color is requested.
 * @return The color code as a string.
 */
const char* const LogLevel_GetColor(const LogLevel level);

/**
 * @brief Array of names associated with each log level.
 *
 * The names represent the string labels for each log level (e.g., "ERROR", "INFO").
 */
extern const char* const LOG_LEVEL_NAMES[LOG_LEVEL_COUNT];

/**
 * @brief Returns the name associated with a given log level.
 *
 * @param level: The log level for which the name is requested.
 * @return The name of the log level as a string.
 */
const char* const LogLevel_GetName(const LogLevel level);