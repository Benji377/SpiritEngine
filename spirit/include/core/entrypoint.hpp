#pragma once

extern Spirit::Application* Spirit::CreateApplication(ApplicationCommandLineArgs args);

int main(int argc, char** argv) {
	Spirit::Log::Init();
	auto app = Spirit::CreateApplication({ argc, argv });
	app->Run();
	delete app;
}
