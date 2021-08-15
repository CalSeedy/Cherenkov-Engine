include "./vendor/premake/premake_customisation/solution_items.lua"
workspace "Cherenkov"
	architecture "x86_64"
	startproject "Spectrum"

	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}
	
	solution_items 
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Cherenkov/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Cherenkov/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Cherenkov/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Cherenkov/vendor/glm"
IncludeDir["stb"] = "%{wks.location}/Cherenkov/vendor/stb"
IncludeDir["EnTT"] = "%{wks.location}/Cherenkov/vendor/EnTT/single_include"
IncludeDir["yaml"] = "%{wks.location}/Cherenkov/vendor/yaml/include"
IncludeDir["imguizmo"] = "%{wks.location}/Cherenkov/vendor/ImGuizmo"


group  "Dependencies"
include "vendor/premake"
include "Cherenkov/vendor/GLFW"
include "Cherenkov/vendor/Glad"
include "Cherenkov/vendor/imgui"
include "Cherenkov/vendor/yaml"
group ""


include "Cherenkov"
include "Sandbox"
include "Spectrum"
