#pragma once

// Color and style escape sequences for terminal output.

// Reset all styles to default
#define LOG_STYLE_RESET          "\033[0m"

// Bold text style
#define LOG_STYLE_BOLD           "\033[1m"

// Text colors
#define LOG_STYLE_WHITE_TEXT     "\033[97m"
#define LOG_STYLE_BLACK_TEXT     "\033[30m"
#define LOG_STYLE_RED_TEXT       "\033[31m"
#define LOG_STYLE_YELLOW_TEXT    "\033[33m"
#define LOG_STYLE_GREEN_TEXT     "\033[32m"
#define LOG_STYLE_BLUE_TEXT      "\033[34m"
#define LOG_STYLE_CYAN_TEXT      "\033[36m"

// Background color
#define LOG_STYLE_RED_BACKGROUND "\033[41m"
