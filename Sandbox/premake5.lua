project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Cherenkov/vendor/spdlog/include",
		"%{wks.location}/Cherenkov/src",
		"%{wks.location}/Cherenkov/vendor",
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
