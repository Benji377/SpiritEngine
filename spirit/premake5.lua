project "SpiritEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
	
	pchheader "include/sprtpch.hpp"
	pchsource "src/sprtpch.cpp"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.cpp",
		"include/**.hpp"
	}

	includedirs {
		"include",
		"platform"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "off"
		files {
			"platform/windows/src/**.cpp",
			"platform/windows/include/**.hpp"
		}

		defines {
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "system:linux"
		links { "pthread", "glfw" }
		systemversion "latest"

		files {
			"platform/linux/src/**.cpp",
			"platform/linux/**.hpp"
		}

		defines {
			"_GLFW_X11",
			"SPDLOG_FMT_EXTERNAL"
		}

	filter { "system:windows", "configurations:Debug" }
		buildoptions "/MTd"

	filter { "system:linux", "configurations:Debug" }
		buildoptions "-g"

	filter { "configurations:Debug" }
		runtime "Debug"
		symbols "on"
		defines "SPRT_DEBUG"

	filter { "system:windows", "configurations:Release" }
		buildoptions "/MT"

	filter { "configurations:Release" }
		runtime "Release"
		optimize "on"
		defines "SPRT_RELEASE"
