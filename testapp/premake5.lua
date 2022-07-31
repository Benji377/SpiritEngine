project "TestApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	links {
		"SpiritEngine"
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"include",
		"%{wks.location}/spirit/include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "off"

		files {
			"platform/windows/src/**.cpp",
			"platform/windows/src/**.hpp",
		}

	filter "system:linux"
		links { "pthread", "fmt", "X11" }
		systemversion "latest"

		files {
			"platform/linux/src/**.cpp",
			"platform/linux/include/**.hpp",
		}

		defines {
			"_GLFW_X11",
			"SPDLOG_FMT_EXTERNAL"
		}

	filter "configurations:Debug"
		defines "SPRT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SPRT_RELEASE"
		runtime "Release"
		optimize "on"
