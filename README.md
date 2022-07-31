# Spirit Engine

# Building
## Premake
Generate a build file using premake.

`premake5 <buildtype>`

For a full list of build types, see [the Premake docs](https://premake.github.io/docs/Using-Premake), but some include

- gmake2 - For Unix Makefiles
- gmake - Don't use, deprecated
- vs(year) - For Visual Studio projects. Year can be any VS year from 2005 to 2022

The premake5 Windows binary is included in `vendor` if you don't have a version installed.

## Required Libraries
- GLM (included in `vendor`)
- GLEW
- GLFW3
- SPDlog (included in `vendor`)

On Windows you'll have to manually install any non-included libs in a path the linker can find them and the headers somewhere the compiler can find them. If you're unsure, investigate the $(VC_IncludePath) and $(VC_LibraryPath) variables to see where the heck Windows decides where the files should go. It's important to install libs in the default directory so everyone's linker knows where to find them.

# Using
## Entry Point
The engine comes with an entry point that instantiates an app and runs it. The `Spirit::CreateApplication` function is what you will define in your app. An example of such a definition is as follows

## Making your App
```c++
Spirit::Application* Spirit::CreateApplication(Spirit::ApplicationCommandLineArgs args) {
	ApplicationSpecification spec;
	spec.Name = "TestApp";
	spec.WorkingDirectory = "testapp";
	spec.CommandLineArgs = args;
	return new Testapp(spec);
}
```

In this example case, the application `Testapp` can be defined as the following.

```c++
class Testapp : public Spirit::Application {
	public:
		Testapp(const Spirit::ApplicationSpecification& specification) : Spirit::Application(specification) {
			PushLayer(new TestLayer());
		}
		~Testapp() {}
};
```

The final thing your app needs is a layer, `TestLayer` is defined as the following.

```c++
class TestLayer : public Spirit::Layer {
	public:
	TestLayer() : Layer("Test") { }

	void OnAttach() override {
		SPRT_INFO("Starting Spirit Application");
	}
};
```

Layer Methods

```c++
virtual void OnAttach() {}
virtual void OnDetach() {}
virtual void OnUpdate() {}
virtual void OnEvent(Event& event) {}

inline const std::string& GetName() const { return m_DebugName; }
```

# Features
Since the engine is in such early stages, this list a planned features list instead of an implemented one

# Game Types
- 3D
- 2D

# Rendering APIs
- OpenGL
- Vulkan
- DirectX (Maybe, if anyone wants to do it. I'm done with MS junk personally)
- None (Used for things like game servers)

# Platforms
- Windows
- Linux

# Goals
- Fast
- Flexible
- No [Cringe](https://gist.github.com/zja203/d5fd7c61171e934c1460d4cc1152d0c6)
