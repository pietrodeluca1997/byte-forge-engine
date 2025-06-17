#pragma once

#ifdef BF_ENGINE_DLL_BUILD
	// Defines the export symbol for the ByteForge Engine when building the DLL.
	// This ensures the function declarations are available for dynamic linking.
	#define BF_ENGINE_API __declspec(dllexport)
#else
	// Defines the import symbol for the ByteForge Engine when using the DLL.
	// This makes the functions from the DLL accessible to the client code.
	#define BF_ENGINE_API __declspec(dllimport)
#endif