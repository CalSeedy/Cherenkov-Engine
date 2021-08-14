project "Cherenkov"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ckpch.h"
	pchsource "src/ckpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb/**.h",
		"vendor/EnTT/single_include/entt/entt.h"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.EnTT}",
		"%{IncludeDir.yaml}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"yaml",
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
