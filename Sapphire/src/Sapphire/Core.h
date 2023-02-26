#pragma once

#ifdef SP_DEBUG
	#define SP_ENABLE_ASSERTS
#endif

#ifdef SP_ENABLE_ASSERTS
	#define SP_ASSERT(x, ...) { if (!(x)) { SP_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SP_CORE_ASSERT(x, ...) { if (!(x)) { SP_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SP_ASSERT(x, ...)
	#define SP_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)