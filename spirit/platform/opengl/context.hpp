#pragma once

#include "renderer/graphics_context.hpp"
#include "core/app_spec.hpp"

struct GLFWwindow;

namespace Spirit {
	class OpenGLContext : public GraphicsContext {
		public:
			OpenGLContext(GLFWwindow* windowHandle);

			virtual void Init(ApplicationCommandLineArgs& args) override;
			virtual void SwapBuffers() override;
		private:
			GLFWwindow* m_WindowHandle;
	};
}
