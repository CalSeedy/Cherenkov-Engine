workspace "Cherenkov"
	architecture "x86_64"
	startproject "Spectrum"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Cherenkov/vendor/GLFW/include"
IncludeDir["Glad"] = "Cherenkov/vendor/Glad/include"
IncludeDir["ImGui"] = "Cherenkov/vendor/imgui"
IncludeDir["glm"] = "Cherenkov/vendor/glm"
IncludeDir["stb"] = "Cherenkov/vendor/stb"
IncludeDir["EnTT"] = "Cherenkov/vendor/EnTT/single_include"

group  "Dependencies"
include "Cherenkov/vendor/GLFW"
include "Cherenkov/vendor/Glad"
include "Cherenkov/vendor/imgui"
group ""

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
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/EnTT/single_include/entt/entt.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.EnTT}"
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
			"CK_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"Cherenkov"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		runtime "Release"
		optimize "on"

project "Spectrum"
	location "Spectrum"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/EnTT/single_include/entt/entt.h"
	}

	includedirs
	{
		"Cherenkov/vendor/spdlog/include",
		"Cherenkov/src",
		"Cherenkov/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.EnTT}"
	}

	links
	{
		"Cherenkov"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CK_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CK_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		runtime "Release"
		optimize "on"