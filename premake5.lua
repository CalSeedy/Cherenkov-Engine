workspace "Cherenkov"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Cherenkov/vendor/GLFW/include"

include "Cherenkov/vendor/GLFW"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Cherenkov/vendor/spdlog/include",
		"Cherenkov/src"
	}

	links 
	{
		"Cherenkov"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"CK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CK_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CK_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"

project "Cherenkov"
	location "Cherenkov"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ckpch.h"
	pchsource "Cherenkov/src/ckpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"CK_PLATFORM_WINDOWS",
			"CK_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CK_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "CK_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		buildoptions "/MD"
		optimize "On"

