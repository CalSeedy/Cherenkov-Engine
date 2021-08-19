include "./vendor/premake/premake_customisation/solution_items.lua"
include "Dependencies.lua"

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
