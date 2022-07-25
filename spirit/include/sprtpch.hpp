#pragma once

#include <iostream>
#include <cstdio>

#include "core/base.hpp"

#ifdef SPRT_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
#if defined(SPRT_PLATFORM_LINUX) || defined(SPRT_PLATFORM_MAC)
	#include <stdlib.h>
	#include <signal.h>
#endif
