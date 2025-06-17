#pragma once

/**
 * @brief Represents a game level in the engine.
 *
 * A `GameLevel` holds information about the level's name and its file path. It is used to load and manage
 * levels within the game.
 */
typedef struct GameLevel
{
    /**
     * @brief The name of the game level.
     *
     * This field holds the identifier or name of the level. It is used for display and level management purposes.
     */
    char* level_name;

    /**
     * @brief The file path to the level's resources.
     *
     * This field holds the path to the level's file, which can contain data such as environment settings,
     * entity definitions, and other level-specific information.
     */
    char* level_path;
} GameLevel;