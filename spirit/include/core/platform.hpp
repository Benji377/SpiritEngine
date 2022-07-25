#pragma once

#include <string>

// Platform detection
#ifdef _WIN32
	#ifdef _WIN64
		#define SPRT_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define SPRT_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define SPRT_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform!"
	#endif
#elif defined(__ANDROID__)
	#define SPRT_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define SPRT_PLATFORM_LINUX
#else
	#error "Unknown platform!"
#endif // End of platform detection

#define eprintf(format, ...) fprintf(stderr, format, __VA_ARGS__)

namespace Spirit {
	class FileDialogs {
		public:
			// These return empty strings if cancelled
			static std::string OpenFile(const char* filter);
			static std::string SaveFile(const char* filter);
	};

	class Time {
		public:
			static float GetTime();
	};
}
