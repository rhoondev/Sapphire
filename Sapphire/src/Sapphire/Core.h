#pragma once

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SAPPHIRE_API __declspec(dllexport)
	#else
		#define SAPPHIRE_API __declspec(dllimport)
	#endif
#else
	#error Sapphire Engine only supports Windows!
#endif

#ifdef SP_ENABLE_ASSERTS
	#define SP_ASSERT(x, ...) { if (!(x)) { SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SP_CORE_ASSERT(x, ...) { if (!(x)) { SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SP_ASSERT(x, ...)
	#define SP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)