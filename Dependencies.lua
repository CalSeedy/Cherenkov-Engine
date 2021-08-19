VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Cherenkov/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Cherenkov/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Cherenkov/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Cherenkov/vendor/glm"
IncludeDir["stb"] = "%{wks.location}/Cherenkov/vendor/stb"
IncludeDir["EnTT"] = "%{wks.location}/Cherenkov/vendor/EnTT/single_include"
IncludeDir["yaml"] = "%{wks.location}/Cherenkov/vendor/yaml/include"
IncludeDir["imguizmo"] = "%{wks.location}/Cherenkov/vendor/ImGuizmo"
IncludeDir["shaderc"] = "%{wks.location}/Cherenkov/vendor/shaderc/libshaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Cherenkov/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/Cherenkov/vendor/VulkanSDK/Lib"
LibraryDir["VulkanSDK_DebugDLL"] = "%{wks.location}/Cherenkov/vendor/VulkanSDK/Bin"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
