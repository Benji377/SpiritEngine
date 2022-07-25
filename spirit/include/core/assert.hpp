#pragma once

#include "core/log.hpp"
#include <filesystem>

#ifdef SPRT_ENABLE_ASSERTS
	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define SPRT_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { SPRT##type##ERROR(msg, __VA_ARGS__); SPRT_DEBUGBREAK(); } }
	#define SPRT_INTERNAL_ASSERT_WITH_MSG(type, check, ...) SPRT_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define SPRT_INTERNAL_ASSERT_NO_MSG(type, check) SPRT_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SPRT_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

	#define SPRT_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define SPRT_INTERNAL_ASSERT_GET_MACRO(...) SPRT_EXPAND_MACRO( SPRT_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, SPRT_INTERNAL_ASSERT_WITH_MSG, SPRT_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define SPRT_ASSERT(...) SPRT_EXPAND_MACRO( SPRT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define SPRT_CORE_ASSERT(...) SPRT_EXPAND_MACRO( SPRT_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define SPRT_ASSERT(...)
	#define SPRT_CORE_ASSERT(...)
#endif
