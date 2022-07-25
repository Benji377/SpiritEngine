#include "spirit.hpp"

class TestLayer : public Spirit::Layer {
	public:
	TestLayer() : Layer("Test") { }

	void OnAttach() override {
		SPRT_INFO("Starting Spirit Application");
	}
};

class Testapp : public Spirit::Application {
	public:
		Testapp(const Spirit::ApplicationSpecification& specification) : Spirit::Application(specification) {
			PushLayer(new TestLayer());
		}
		~Testapp() {}
};

Spirit::Application* Spirit::CreateApplication(Spirit::ApplicationCommandLineArgs args) {
	ApplicationSpecification spec;
	spec.Name = "TestApp";
	spec.WorkingDirectory = ".";
	spec.CommandLineArgs = args;
	return new Testapp(spec);
}
