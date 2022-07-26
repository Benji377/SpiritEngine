#pragma once
namespace Spirit {
	struct ApplicationCommandLineArgs {
		int count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const {
			return Args[index];
		}
	};

	struct ApplicationSpecification {
		std::string Name = "Spirit Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};
}
