#include <GL/glew.h>
#include <GL/glut.h>
#include "core/window.hpp"
#include "sprtpch.hpp"

namespace Spirit {
	Window::Window(WindowProps props, ApplicationCommandLineArgs args) {
		/* res->width = width; */
		/* res->height = height; */
		/* res->title = title; */
		width = 1920;
		height = 1080;
		title = "Spirit App";

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 16);

		windowPtr = (void*)glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (windowPtr == nullptr) {
			glfwTerminate();
		}

		glfwSetWindowUserPointer((GLFWwindow*)windowPtr, (void*)this);
		makeContextCurrent();

		/* glfwSetCursorPosCallback((GLFWwindow*)windowPtr, Input::mouseCallback); */
		/* glfwSetKeyCallback((GLFWwindow*)windowPtr, Input::keyCallback); */
		/* glfwSetFramebufferSizeCallback((GLFWwindow*)windowPtr, resizeCallback); */

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		int monitorX, monitorY;
		glfwGetMonitorPos(monitor, &monitorX, &monitorY);

		int windowWidth, windowHeight;
		glfwGetWindowSize((GLFWwindow*)windowPtr, &windowWidth, &windowHeight);

		glfwSetWindowPos((GLFWwindow*)windowPtr,
			monitorX + (mode->width - windowWidth) / 2,
			monitorY + (mode->height - windowHeight) / 2);

		
		glutInit(&args.count, args.Args);
		glutCreateWindow(title);
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			eprintf("Error: %s\n", glewGetErrorString(err));
		}
		printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glViewport(0, 0, width, height);
	}

	void Window::free(Window* window) {
		delete window;
	}

	void Window::setCursorMode(CursorMode cursorMode) {
		int glfwCursorMode =
			cursorMode == CursorMode::Locked ? GLFW_CURSOR_DISABLED :
			cursorMode == CursorMode::Normal ? GLFW_CURSOR_NORMAL :
			cursorMode == CursorMode::Hidden ? GLFW_CURSOR_HIDDEN :
			GLFW_CURSOR_HIDDEN;

		glfwSetInputMode((GLFWwindow*)windowPtr, GLFW_CURSOR, glfwCursorMode);
	}

	void Window::makeContextCurrent() {
		glfwMakeContextCurrent((GLFWwindow*)windowPtr);
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose((GLFWwindow*)windowPtr);
	}

	void Window::swapBuffers() {
		glfwSwapBuffers((GLFWwindow*)windowPtr);
	}

	void Window::setVSync(bool on) {
		if (on) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
	}

	void Window::update(float dt) { }

	void Window::cleanup() {
		glfwTerminate();
	}
}
