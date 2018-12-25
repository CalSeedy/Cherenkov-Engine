workspace "Cherenkov"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

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

project "Cherenkov"
	location "Cherenkov"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"		
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
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "CK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CK_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "CK_DISTRIBUTION"
		optimize "On"

