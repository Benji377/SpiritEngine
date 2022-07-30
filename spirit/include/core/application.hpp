#pragma once
#include "layer_stack.hpp"
#include "events/event.hpp"
#include "core/timestep.hpp"
#include "core/window.hpp"
#include "events/app_event.hpp"
#include "core/app_spec.hpp"
#include "renderer/shader.hpp"
#include "renderer/buffer.hpp"
#include "renderer/vertex_array.hpp"

int main(int argc, char** argv);

namespace Spirit {
	class Application {
		public:
			Application(const ApplicationSpecification& specification);
			virtual ~Application();
			Window& GetWindow() { return *m_Window; }
			void Close();
			static Application& Get() { return *s_Instance; }
			const ApplicationSpecification& GetSpecification() const { return m_Specification; }

			void OnEvent(Event& e);
			bool OnWindowClose(WindowCloseEvent& e);

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* layer);
		private:
			void Run();
			ApplicationSpecification m_Specification;
			std::unique_ptr<Window> m_Window;
			bool m_Running = true;
			bool m_Minimized = false;
			float m_LastFrameTime = 0.0f;
			static Application* s_Instance;
			LayerStack m_LayerStack;
			std::shared_ptr<VertexArray> m_VertexArray, m_VertexBuffer, m_IndexBuffer;
			std::shared_ptr<Shader> m_Shader;

			std::shared_ptr<Shader> m_BlueShader;
			std::shared_ptr<VertexArray> m_SquareVA;
			friend int ::main(int argc, char** argv);
	};
	// To be defined in client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}
