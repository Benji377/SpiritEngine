#pragma once

#include "core/base.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Spirit {
	class Log {
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector) {
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix) {
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion) {
	return os << glm::to_string(quaternion);
}

// Core log macros
#define SPRT_CORE_TRACE(...)    ::Spirit::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPRT_CORE_INFO(...)     ::Spirit::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPRT_CORE_WARN(...)     ::Spirit::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPRT_CORE_ERROR(...)    ::Spirit::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPRT_CORE_CRITICAL(...) ::Spirit::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SPRT_TRACE(...)         ::Spirit::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPRT_INFO(...)          ::Spirit::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPRT_WARN(...)          ::Spirit::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPRT_ERROR(...)         ::Spirit::Log::GetClientLogger()->error(__VA_ARGS__)
#define SPRT_CRITICAL(...)      ::Spirit::Log::GetClientLogger()->critical(__VA_ARGS__)
