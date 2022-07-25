#include "core/application.hpp"
#include "core/platform.hpp"

namespace Spirit {
	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification) : m_Specification(specification) {
		s_Instance = this;

		// Set working directory here
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);

		//m_Window = new Window(WindowProps(m_Specification.Name), specification.CommandLineArgs);
	}

	Application::~Application() {
	}

	void Application::Close() {
		m_Running = false;
	}
	
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		/* dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); */

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		while (m_Running) {
			float time = Time::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
		}
	}
}
