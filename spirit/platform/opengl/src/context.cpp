#include "opengl/context.hpp"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

namespace Spirit {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		SPRT_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init(ApplicationCommandLineArgs& args) {
		glfwMakeContextCurrent(m_WindowHandle);
		glutInit(&args.count, args.Args);
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			SPRT_CORE_ASSERT(err, "Failed to initialize GLEW!");
		}
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}
