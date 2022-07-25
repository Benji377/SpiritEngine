#include "core/platform.hpp"

#include <GLFW/glfw3.h>

namespace Spirit {
	float Time::GetTime() {
		return glfwGetTime();
	}
}
