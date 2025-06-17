// Copyright (c) 2024 Pietro De Luca, Anxious Elephant. All rights reserved.

#include <ByteForgeEngine.h>

#include <stdlib.h>

/**
 * @brief Entry point for the ByteForge Sandbox application.
 *
 * This function initializes and runs the ByteForge Engine with the provided command-line arguments.
 * 
 * If the engine fails to start, the program exits with a failure code. Otherwise, it terminates successfully.
 *
 * @param argc: Number of command-line arguments.
 * @param argv: Array of command-line argument strings.
 * 
 * @return EXIT_SUCCESS if the engine runs successfully, EXIT_FAILURE otherwise.
 */
int main(int argc, char** argv)
{
    if (!ByteForgeEngine_Start(argc, argv))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}