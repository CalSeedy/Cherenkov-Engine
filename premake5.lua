workspace "Cherenkov"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Cherenkov/vendor/GLFW/include"
IncludeDir["Glad"] = "Cherenkov/vendor/Glad/include"
IncludeDir["ImGui"] = "Cherenkov/vendor/imgui"
IncludeDir["glm"] = "Cherenkov/vendor/glm"

include "Cherenkov/vendor/GLFW"
include "Cherenkov/vendor/Glad"
include "Cherenkov/vendor/imgui"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

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
		"Cherenkov/src",
		"Cherenkov/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Cherenkov"
	}
	
	defines
	{
		"CK_PLATFORM_WINDOWS"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CK_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "CK_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		buildoptions "/MD"
		optimize "on"


project "Cherenkov"
	location "Cherenkov"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ckpch.h"
	pchsource "Cherenkov/src/ckpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CK_PLATFORM_WINDOWS",
			"CK_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		defines "CK_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "CK_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		buildoptions "/MD"
		optimize "on"
