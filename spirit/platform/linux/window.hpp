#pragma once

#include "core/window.hpp"
#include "events/app_event.hpp"
#include "renderer/graphics_context.hpp"
#include "core/app_spec.hpp"

#include <GLFW/glfw3.h>

namespace Spirit {
	class LinuxWindow : public Window {
		public:
			LinuxWindow(const WindowProps& props, ApplicationCommandLineArgs& args);
			virtual ~LinuxWindow();

			void OnUpdate() override;

			inline unsigned int GetWidth() const override { return m_Data.Width; }
			inline unsigned int GetHeight() const override { return m_Data.Height; }

			// Window attributes
			inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
			void SetVSync(bool enabled) override;
			bool IsVSync() const override;
			virtual void Init(const WindowProps& props, ApplicationCommandLineArgs& args);
			virtual void Shutdown();
			inline virtual void* GetNativeWindow() const { return m_Window; }
		private:
			GLFWwindow* m_Window;
			GraphicsContext* m_Context;

			struct WindowData {
				std::string Title;
				unsigned int Width, Height;
				bool VSync;

				EventCallbackFn EventCallback;
			};
			WindowData m_Data;
	};
}
