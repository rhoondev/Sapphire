#pragma once

#ifdef SP_DEBUG
	#define SP_ENABLE_ASSERTS
#endif

#ifdef SP_ENABLE_ASSERTS
	#define CORE_ASSERT_FAILURE(test, message) Console::Assert(test, message)
	#define CORE_ASSERT(test, success, failure) Console::Assert(test, success, failure)
	#define CORE_ERROR(message) Console::LogError(message)
#else
	#define CORE_ASSERT(test, message)
	#define CORE_ASSERT(test, success, failure)
	#define CORE_ERROR(message)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)