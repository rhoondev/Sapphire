#pragma once

#ifdef SAPPHIRE_PLATFORM_WINDOWS
	#ifdef SAPPHIRE_BUILD_DLL
		#define SAPPHIRE_API __declspec(dllexport)
	#else
		#define SAPPHIRE_API __declspec(dllimport)
	#endif
#else
	#error Sapphire Engine only supports Windows!
#endif