#include <GL/glew.h>
#include "linux/window.hpp"
#include "opengl/context.hpp"
#include "renderer/shader.hpp"
#include "core/application.hpp"

namespace Spirit {
	static bool s_GLFWInitialized = false;
	GLuint programID;
	GLuint vertexbuffer;

	static void GLFWErrorCallback(int error, const char* description) {
		SPRT_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props, ApplicationCommandLineArgs args) {
		return new LinuxWindow(props, args);
	}

	LinuxWindow::LinuxWindow(const WindowProps& props, ApplicationCommandLineArgs& args) {
		Init(props, args);
	}

	LinuxWindow::~LinuxWindow() {
		Shutdown();
	}

	void LinuxWindow::Init(const WindowProps& props, ApplicationCommandLineArgs& args) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SPRT_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			SPRT_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init(args);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
		});
		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		static const GLfloat g_vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
		};
		// This will identify our vertex buffer
		vertexbuffer;
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexbuffer);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		programID = LoadShaders( "shaders/vert.glsl", "shaders/frag.glsl" );
	}

	void LinuxWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void LinuxWindow::OnUpdate() {
		glfwPollEvents();
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
				);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
		glUseProgram(programID);
		glfwSwapBuffers(m_Window);
	}

	void LinuxWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool LinuxWindow::IsVSync() const {
		return m_Data.VSync;
	}
}
