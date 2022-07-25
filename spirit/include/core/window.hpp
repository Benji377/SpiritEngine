#pragma once
#include "sprtpch.hpp"
#include <GLFW/glfw3.h>

namespace Spirit {
	enum CursorMode {
		Hidden,
		Locked,
		Normal
	};

	struct WindowProps {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "Spirit Engine", uint32_t width = 1600, uint32_t height = 900) : Title(title), Width(width), Height(height) { }
	};

	class Window {
		int width;
		int height;
		const char* title;
		void* windowPtr;
		public:
		Window(WindowProps props, ApplicationCommandLineArgs args);
		void makeContextCurrent();

		void pollInput();

		void swapBuffers();

		void update(float dt);

		void setCursorMode(CursorMode cursorMode);

		bool shouldClose();

		void setVSync(bool on);
		
		static void resizeCallback(GLFWwindow* windowPtr, int newWidth, int newHeight);

		static void cleanup();

		static void free(Window* window);
	};
}
