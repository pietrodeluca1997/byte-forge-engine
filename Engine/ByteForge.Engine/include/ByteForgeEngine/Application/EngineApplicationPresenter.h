#pragma once

#include "EngineApplicationArguments.h"

/**
 * @brief Displays the introductory presentation for the engine application.
 *
 * This function is called to show the intro screen or information when the application starts.
 * It can use the passed arguments to display relevant information (e.g., version or command-line options).
 *
 * @param arguments: The arguments passed to the engine application at startup.
 *                   These can be used to customize the intro based on input parameters.
 */
void EngineApplicationPresenter_ShowIntroductionMessage(const EngineApplicationArguments* const arguments);

/**
 * @brief Finalizes the engine application presentation.
 *
 * This function is used to show the exit screen or information when application finishes.
 * It might be called at the end of the application.
 */
void EngineApplicationPresenter_ShowExitMessage();