-- Copyright (c) 2024 Pietro De Luca, Anxious Elephant. All rights reserved.

-- PlatformConfiguration.lua

---@class PlatformSettings
---@field target_fps integer Target frames per second for the application.
PlatformSettings =
{
    target_fps = 60
}

---@class PlatformWindow
---@field window_title string Title of the application window.
---@field window_width integer Width of the application window in pixels.
---@field window_height integer Height of the application window in pixels.
PlatformWindow =
{
    window_title = "Asteroids",
    window_width = 1024,
    window_height = 768
}