#pragma once

#include "LogLevel.h"

/**
 * @brief Logs a message with a standard log level.
 *
 * This function is used to log messages with varying log levels (e.g., info, warning, debug).
 * It accepts a format string and a variable number of arguments, similar to `printf`.
 *
 * @param level: The log level indicating the severity or category of the log (e.g., INFO, WARN).
 * @param format: The format string that specifies the log message.
 * @param ...: The variable arguments to be formatted into the log message.
 */
void Logger_StandardLog(const LogLevel level, const char* const format, ...);

/**
 * @brief Logs an message with additional context.
 *
 * This function is used to log error messages and other contexts where more information are needed, including details like the source file,
 * line number, and function name where the error occurred, to help with debugging.
 *
 * @param level: The log level indicating the severity of the error (e.g., ERROR, CRITICAL).
 * @param file_name: The name of the source file where the error occurred.
 * @param code_line: The line number in the source file where the error occurred.
 * @param function_name: The name of the function where the error occurred.
 * @param format: The format string that specifies the log message.
 * @param ...: The variable arguments to be formatted into the log message.
 */
void Logger_DetailedLog(
	const LogLevel level, 
	const char* const file_name, 
	const int code_line, 
	const char* const function_name, 
	const char* const format, ...
);