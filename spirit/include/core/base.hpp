#pragma once

#include "core/platform.hpp"

#include <memory>

#ifdef SPRT_DEBUG
#if defined(SPRT_PLATFORM_WINDOWS)
#define SPRT_DEBUGBREAK() __debugbreak()
#elif defined(SPRT_PLATFORM_LINUX)
#include <signal.h>
#define SPRT_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define SPRT_ENABLE_ASSERTS
#else
#define SPRT_DEBUGBREAK()
#endif

#define SPRT_EXPAND_MACRO(x) x
#define SPRT_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

namespace Spirit {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "core/assert.hpp"
