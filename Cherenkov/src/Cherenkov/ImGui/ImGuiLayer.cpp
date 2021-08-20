#include "ckpch.h"
#include "Cherenkov/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Cherenkov/Core/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <imguizmo.h>

namespace Cherenkov {
	
	struct ImGuiLayer::Theme {
		ImVec4 textOnP;
		ImVec4 primary;
		ImVec4 textOnPVar;
		ImVec4 primaryVar;
		ImVec4 textOnS;
		ImVec4 secondary;
		ImVec4 textOnSVar;
		ImVec4 secondaryVar;

		Theme() = default;
	};

	ImGuiLayer::ColourStyle ImGuiLayer::style = ImGuiLayer::ColourStyle::DarkMode;
	ImGuiLayer::Theme		ImGuiLayer::theme = ImGuiLayer::Theme();

	ImVec4 ImGuiLayer::mixColours(const ImVec4& first, const ImVec4& second, float mixAmount)	{
		mixAmount = std::max(0.0f, std::min(1.0f, mixAmount));
		float a1 = first.w * (1 - mixAmount);
		float a = 1.0f - (1.0f - a1) * (1.0f - second.w);
		float s = second.w * (1.0f - a1) / a;
		return { (1.0f - s) * first.x + s * second.x, (1.0f - s) * first.y + s * second.y, (1.0f - s) * first.z + s * second.z, a };
	}

	ImGuiLayer::Font ImGuiLayer::font = { "assets/Fonts/Source Sans Pro/SourceSansPro-", Window::s_DPIFactor * 18.0f };
	bool ImGuiLayer::fontChange = false;

	std::vector<std::vector<ImVec4>> ImGuiLayer::colourStyles = {};

	/*
	
	//	Text
		colours[ImGuiCol_Text]					= colours[ImGuiCol_Text];
		colours[ImGuiCol_TextDisabled]			= colours[ImGuiCol_TextDisabled];
		colours[ImGuiCol_TextSelectedBg]		= colours[ImGuiCol_TextSelectedBg];

		//	Backgrounds
		colours[ImGuiCol_WindowBg]				= colours[ImGuiCol_WindowBg];
		colours[ImGuiCol_PopupBg]				= colours[ImGuiCol_PopupBg];
			//	Frames
			colours[ImGuiCol_FrameBg]			= colours[ImGuiCol_FrameBg];
			colours[ImGuiCol_FrameBgHovered]	= colours[ImGuiCol_FrameBgHovered];
			colours[ImGuiCol_FrameBgActive]		= colours[ImGuiCol_FrameBgActive];

			//	Title
			colours[ImGuiCol_TitleBg]			= colours[ImGuiCol_TitleBg];
			colours[ImGuiCol_TitleBgActive]		= colours[ImGuiCol_TitleBgActive];
			colours[ImGuiCol_TitleBgCollapsed]	= colours[ImGuiCol_TitleBgCollapsed];

			//	Menu
			colours[ImGuiCol_MenuBarBg]			= colours[ImGuiCol_MenuBarBg];

			//	Scrollbar
			colours[ImGuiCol_ScrollbarBg]		= colours[ImGuiCol_ScrollbarBg];

			//	Docking
			colours[ImGuiCol_DockingEmptyBg]	= colours[ImGuiCol_DockingEmptyBg];

			//	Table
			colours[ImGuiCol_TableHeaderBg]		= colours[ImGuiCol_TableHeaderBg];
			colours[ImGuiCol_TableRowBg]		= colours[ImGuiCol_TableRowBg];
			colours[ImGuiCol_TableRowBgAlt]		= colours[ImGuiCol_TableRowBgAlt];

			//	Nav
			colours[ImGuiCol_NavWindowingDimBg] = colours[ImGuiCol_NavWindowingDimBg];

			//	Modal
			colours[ImGuiCol_ModalWindowDimBg]	= colours[ImGuiCol_ModalWindowDimBg];

		//	Borders
		colours[ImGuiCol_Border]				= colours[ImGuiCol_Border];
		colours[ImGuiCol_BorderShadow]			= colours[ImGuiCol_BorderShadow];


		//	Scrollbar
		colours[ImGuiCol_ScrollbarGrab]			= colours[ImGuiCol_ScrollbarGrab];
		colours[ImGuiCol_ScrollbarGrabHovered]	= colours[ImGuiCol_ScrollbarGrabHovered];
		colours[ImGuiCol_ScrollbarGrabActive]	= colours[ImGuiCol_ScrollbarGrabActive];

		//	Checkmark
		colours[ImGuiCol_CheckMark]				= colours[ImGuiCol_CheckMark];

		//	Slider
		colours[ImGuiCol_SliderGrab]			= colours[ImGuiCol_SliderGrab];
		colours[ImGuiCol_SliderGrabActive]		= colours[ImGuiCol_SliderGrabActive];

		//	Button
		colours[ImGuiCol_Button]				= colours[ImGuiCol_Button];
		colours[ImGuiCol_ButtonHovered]			= colours[ImGuiCol_ButtonHovered];
		colours[ImGuiCol_ButtonActive]			= colours[ImGuiCol_ButtonActive];

		//	Header
		colours[ImGuiCol_Header]				= colours[ImGuiCol_Header];
		colours[ImGuiCol_HeaderHovered]			= colours[ImGuiCol_HeaderHovered];
		colours[ImGuiCol_HeaderActive]			= colours[ImGuiCol_HeaderActive];

		//	Separator
		colours[ImGuiCol_Separator]				= colours[ImGuiCol_Separator];
		colours[ImGuiCol_SeparatorHovered]		= colours[ImGuiCol_SeparatorHovered];
		colours[ImGuiCol_SeparatorActive]		= colours[ImGuiCol_SeparatorActive];

		//	Grip
		colours[ImGuiCol_ResizeGrip]			= colours[ImGuiCol_ResizeGrip];
		colours[ImGuiCol_ResizeGripHovered]		= colours[ImGuiCol_ResizeGripHovered];
		colours[ImGuiCol_ResizeGripActive]		= colours[ImGuiCol_ResizeGripActive];

		//	Tab
		colours[ImGuiCol_Tab]					= colours[ImGuiCol_Tab];
		colours[ImGuiCol_TabHovered]			= colours[ImGuiCol_TabHovered];
		colours[ImGuiCol_TabActive]				= colours[ImGuiCol_TabActive];
		colours[ImGuiCol_TabUnfocused]			= colours[ImGuiCol_TabUnfocused];
		colours[ImGuiCol_TabUnfocusedActive]	= colours[ImGuiCol_TabUnfocusedActive];

		//	Docking
		colours[ImGuiCol_DockingPreview]		= colours[ImGuiCol_DockingPreview];

		//	Plot
		colours[ImGuiCol_PlotLines]				= colours[ImGuiCol_PlotLines];
		colours[ImGuiCol_PlotLinesHovered]		= colours[ImGuiCol_PlotLinesHovered];
		colours[ImGuiCol_PlotHistogram]			= colours[ImGuiCol_PlotHistogram];
		colours[ImGuiCol_PlotHistogramHovered]	= colours[ImGuiCol_PlotHistogramHovered];

		//	Table
		colours[ImGuiCol_TableBorderStrong]		= colours[ImGuiCol_TableBorderStrong];
		colours[ImGuiCol_TableBorderLight]		= colours[ImGuiCol_TableBorderLight];

		//	Drag/Drop
		colours[ImGuiCol_DragDropTarget]		= colours[ImGuiCol_DragDropTarget];

		//	Nav
		colours[ImGuiCol_NavHighlight]			= colours[ImGuiCol_NavHighlight];
		colours[ImGuiCol_NavWindowingHighlight] = colours[ImGuiCol_NavWindowingHighlight];
	
	*/

	void ImGuiLayer::initStyles() {
		for (uint32_t i = 0; i < (uint32_t)ImGuiLayer::ColourStyle::COUNT; i++) {
			colourStyles.push_back(std::vector<ImVec4>{});
		}

		std::vector<ImVec4> tmp;
		tmp.resize(ImGuiCol_COUNT);
		ImGuiLayer::theme = ImGuiLayer::Theme();
		{
			auto& colours = ImGui::GetStyle().Colors;
			for (auto i = 0; i < ImGuiCol_COUNT; i++) {
				tmp[i] = colours[i];
			}
		} colourStyles[(uint32_t)ImGuiLayer::ColourStyle::Default] = tmp;

		const ImVec4 defaultLightBg{ 0.9268f, 0.9268f, 0.9268f, 1.0f };
		const ImVec4 defaultDarkBg{ 0.0742f, 0.0742f, 0.0742f, 1.0f };

		tmp.clear();
		tmp.resize(ImGuiCol_COUNT);
		{
			ImGuiLayer::theme.primary = ImVec4{ 0.12f, 0.75f, 0.99f, 1.0f };
			ImGuiLayer::theme.primaryVar = ImVec4{ 0.23f, 0.68f, 0.84f, 1.0f };
			ImGuiLayer::theme.secondary = ImVec4{ 0.42f, 0.87f, 1.00f, 1.0f };
			ImGuiLayer::theme.secondaryVar = ImVec4{ 0.47f, 0.87f, 1.0f, 1.0f };
			ImGuiLayer::theme.textOnP = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnPVar = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnS = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnSVar = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
		}
		{
			tmp = colourStyles[(uint32_t)ImGuiLayer::ColourStyle::Default];
			tmp[ImGuiCol_Text] = ImGuiLayer::theme.textOnP;
			tmp[ImGuiCol_TextDisabled] = ImGuiLayer::theme.textOnP; tmp[ImGuiCol_TextDisabled].w = 0.5f;
			tmp[ImGuiCol_TextSelectedBg] = ImGuiLayer::theme.textOnP; tmp[ImGuiCol_TextSelectedBg].w = 0.2f;

			tmp[ImGuiCol_WindowBg] = defaultLightBg;
			tmp[ImGuiCol_PopupBg] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.secondary, 0.8f);
			tmp[ImGuiCol_FrameBg] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.primaryVar, 0.8f);
			tmp[ImGuiCol_FrameBgHovered] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.secondary, 0.8f);
			tmp[ImGuiCol_FrameBgActive] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.primary, 0.5f);
			tmp[ImGuiCol_TitleBg] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_TitleBgActive] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_TitleBgCollapsed] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_MenuBarBg] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.secondary, 0.5f);
			tmp[ImGuiCol_ScrollbarBg] = tmp[ImGuiCol_FrameBgHovered];
			tmp[ImGuiCol_DockingEmptyBg] = tmp[ImGuiCol_FrameBg];

			tmp[ImGuiCol_Header] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_HeaderHovered] = ImGuiLayer::theme.secondaryVar;
			tmp[ImGuiCol_HeaderActive] = ImGuiLayer::theme.primary;

			
			tmp[ImGuiCol_Tab] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_TabHovered] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.primary, 0.1f);
			tmp[ImGuiCol_TabActive] = defaultLightBg;
			tmp[ImGuiCol_TabUnfocused] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_TabUnfocusedActive] = ImGuiLayer::theme.primaryVar;

			tmp[ImGuiCol_TableHeaderBg] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_TableRowBg] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.primary, 0.4f);
			tmp[ImGuiCol_TableRowBgAlt] = ImGuiLayer::mixColours(defaultLightBg, ImGuiLayer::theme.primaryVar, 0.4f);
			tmp[ImGuiCol_NavWindowingDimBg] = defaultLightBg; tmp[ImGuiCol_NavWindowingDimBg].w = 0.1f;
			tmp[ImGuiCol_ModalWindowDimBg] = defaultLightBg; tmp[ImGuiCol_ModalWindowDimBg].w = 0.1f;
			tmp[ImGuiCol_Border] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_BorderShadow] = defaultDarkBg;
			tmp[ImGuiCol_ScrollbarGrab] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_ScrollbarGrabHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_ScrollbarGrabActive] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_CheckMark] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_SliderGrab] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_SliderGrabActive] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_Button] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_ButtonHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_ButtonActive] = ImGuiLayer::theme.secondary;
			
			tmp[ImGuiCol_Separator] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_SeparatorHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_SeparatorActive] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_ResizeGrip] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_ResizeGripHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_ResizeGripActive] = ImGuiLayer::theme.secondary;
			
			tmp[ImGuiCol_DockingPreview] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_PlotLines] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_PlotLinesHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_PlotHistogram] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_PlotHistogramHovered] = ImGuiLayer::theme.secondaryVar;
			tmp[ImGuiCol_TableBorderStrong] = defaultDarkBg;
			tmp[ImGuiCol_TableBorderLight] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_DragDropTarget] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_NavHighlight] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_NavWindowingHighlight] = ImGuiLayer::theme.primary;
			
		} colourStyles[(uint32_t)ImGuiLayer::ColourStyle::LightMode] = tmp;

		tmp.clear();
		tmp.resize(ImGuiCol_COUNT);
		{
			ImGuiLayer::theme.primary = ImVec4{ 0.12f, 0.75f, 0.99f, 1.0f };
			ImGuiLayer::theme.primaryVar = ImVec4{ 0.23f, 0.68f, 0.84f, 1.0f };
			ImGuiLayer::theme.secondary = ImVec4{ 0.0f, 0.49f, 0.70f, 1.0f };
			ImGuiLayer::theme.secondaryVar = ImVec4{ 0.0f, 0.49f, 0.64f, 1.0f };
			ImGuiLayer::theme.textOnP = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnPVar = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
			ImGuiLayer::theme.textOnS = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnSVar = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
		}
		{
			tmp = colourStyles[(uint32_t)ImGuiLayer::ColourStyle::Default];
			tmp[ImGuiCol_Text] = ImGuiLayer::theme.textOnPVar;
			tmp[ImGuiCol_TextDisabled] = ImGuiLayer::theme.textOnPVar; tmp[ImGuiCol_TextDisabled].w = 0.5f;
			tmp[ImGuiCol_TextSelectedBg] = ImGuiLayer::theme.textOnPVar; tmp[ImGuiCol_TextSelectedBg].w = 0.2f;

			tmp[ImGuiCol_WindowBg] = defaultDarkBg;
			tmp[ImGuiCol_PopupBg] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.secondary, 0.8f);
			tmp[ImGuiCol_FrameBg] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.primaryVar, 0.8f);
			tmp[ImGuiCol_FrameBgHovered] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.secondary, 0.8f);
			tmp[ImGuiCol_FrameBgActive] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.primary, 0.5f);
			tmp[ImGuiCol_TitleBg] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_TitleBgActive] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_TitleBgCollapsed] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_MenuBarBg] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.secondary, 0.5f);
			tmp[ImGuiCol_ScrollbarBg] = tmp[ImGuiCol_FrameBgHovered];
			tmp[ImGuiCol_DockingEmptyBg] = tmp[ImGuiCol_FrameBg];

			tmp[ImGuiCol_Header] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_HeaderHovered] = ImGuiLayer::theme.secondaryVar;
			tmp[ImGuiCol_HeaderActive] = ImGuiLayer::theme.primary;


			tmp[ImGuiCol_Tab] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_TabHovered] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.primary, 0.1f);
			tmp[ImGuiCol_TabActive] = defaultDarkBg;
			tmp[ImGuiCol_TabUnfocused] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_TabUnfocusedActive] = ImGuiLayer::theme.primaryVar;

			tmp[ImGuiCol_TableHeaderBg] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_TableRowBg] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.primary, 0.4f);
			tmp[ImGuiCol_TableRowBgAlt] = ImGuiLayer::mixColours(defaultDarkBg, ImGuiLayer::theme.primaryVar, 0.4f);
			tmp[ImGuiCol_NavWindowingDimBg] = defaultDarkBg; tmp[ImGuiCol_NavWindowingDimBg].w = 0.1f;
			tmp[ImGuiCol_ModalWindowDimBg] = defaultDarkBg; tmp[ImGuiCol_ModalWindowDimBg].w = 0.1f;
			tmp[ImGuiCol_Border] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_BorderShadow] = defaultDarkBg;
			tmp[ImGuiCol_ScrollbarGrab] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_ScrollbarGrabHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_ScrollbarGrabActive] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_CheckMark] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_SliderGrab] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_SliderGrabActive] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_Button] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_ButtonHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_ButtonActive] = ImGuiLayer::theme.secondary;

			tmp[ImGuiCol_Separator] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_SeparatorHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_SeparatorActive] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_ResizeGrip] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_ResizeGripHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_ResizeGripActive] = ImGuiLayer::theme.secondary;

			tmp[ImGuiCol_DockingPreview] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_PlotLines] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_PlotLinesHovered] = ImGuiLayer::theme.primaryVar;
			tmp[ImGuiCol_PlotHistogram] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_PlotHistogramHovered] = ImGuiLayer::theme.secondaryVar;
			tmp[ImGuiCol_TableBorderStrong] = defaultDarkBg;
			tmp[ImGuiCol_TableBorderLight] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_DragDropTarget] = ImGuiLayer::theme.primary;
			tmp[ImGuiCol_NavHighlight] = ImGuiLayer::theme.secondary;
			tmp[ImGuiCol_NavWindowingHighlight] = ImGuiLayer::theme.primary;
			
		} colourStyles[(uint32_t)ImGuiLayer::ColourStyle::DarkMode] = tmp;
	}

	void ImGuiLayer::changeFonts() {
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->Clear();
		if (std::strcmp(ImGuiLayer::font.path.c_str(), "") != 0) {
			io.FontDefault = io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Regular.ttf")).c_str(), ImGuiLayer::font.size);
			io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Bold.ttf")).c_str(), Window::s_DPIFactor * ImGuiLayer::font.size);
			io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Italic.ttf")).c_str(), Window::s_DPIFactor * ImGuiLayer::font.size);
			io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("BoldItalic.ttf")).c_str(), Window::s_DPIFactor * ImGuiLayer::font.size);
		} else
			io.FontDefault = io.Fonts->AddFontDefault();
		io.Fonts->Build();
		ImGui_ImplOpenGL3_CreateFontsTexture();
	}

	void ImGuiLayer::setTheme(ColourStyle style) {
		auto& imStyle = ImGui::GetStyle();
		auto& colours = imStyle.Colors;

		switch (style) {
		case ColourStyle::Default:
			ImGuiLayer::style = ColourStyle::Default;
			ImGuiLayer::theme = ImGuiLayer::Theme();
			break;
		case ColourStyle::LightMode:
			ImGuiLayer::style = ColourStyle::LightMode;
			ImGuiLayer::theme.primary = ImVec4{ 0.12f, 0.75f, 0.99f, 1.0f };
			ImGuiLayer::theme.primaryVar = ImVec4{ 0.23f, 0.68f, 0.84f, 1.0f };
			ImGuiLayer::theme.secondary = ImVec4{ 0.42f, 0.87f, 1.00f, 1.0f };
			ImGuiLayer::theme.secondaryVar = ImVec4{ 0.47f, 0.87f, 1.0f, 1.0f };
			ImGuiLayer::theme.textOnP = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnPVar = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnS = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnSVar = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			break;
		case ColourStyle::DarkMode:
			ImGuiLayer::style = ColourStyle::DarkMode;
			ImGuiLayer::theme.primary = ImVec4{ 0.12f, 0.75f, 0.99f, 1.0f };
			ImGuiLayer::theme.primaryVar = ImVec4{ 0.23f, 0.68f, 0.84f, 1.0f };
			ImGuiLayer::theme.secondary = ImVec4{ 0.0f, 0.49f, 0.70f, 1.0f };
			ImGuiLayer::theme.secondaryVar = ImVec4{ 0.0f, 0.49f, 0.64f, 1.0f };
			ImGuiLayer::theme.textOnP = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnPVar = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
			ImGuiLayer::theme.textOnS = ImVec4{ 0.0f, 0.0f, 0.0f, 1.0f };
			ImGuiLayer::theme.textOnSVar = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
			break;
		default:
			CK_CORE_ASSERT(false, "Unknown ColourStyle!");
			break;
		}
		uint32_t c = 0;
		for (auto col : colourStyles[(uint32_t)ImGuiLayer::style]) {
			colours[c] = col;
			c++;
		}
		imStyle.ScaleAllSizes(Window::s_DPIFactor);
	}

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
	}

	void ImGuiLayer::onAttach() {
		CK_PROFILE_FUNCTION();
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		io.FontDefault = io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Regular.ttf")).c_str(), ImGuiLayer::font.size);
		io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Bold.ttf")).c_str(), ImGuiLayer::font.size);
		io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Italic.ttf")).c_str(), ImGuiLayer::font.size);
		io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("BoldItalic.ttf")).c_str(), ImGuiLayer::font.size);
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
		initStyles();
		setTheme(ImGuiLayer::ColourStyle::DarkMode);

		Application& app = Application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());
		fontChange = false;

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
		
	}

	void ImGuiLayer::onDetach()	{
		CK_PROFILE_FUNCTION();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::onEvent(Event& e)	{
		if (m_Blocking) {
			ImGuiIO& io = ImGui::GetIO();
			e.m_Handled |= e.inCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.m_Handled |= e.inCategory(EventCategoryKeyBoard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::start() {
		CK_PROFILE_FUNCTION();
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
	}

	void ImGuiLayer::stop()	{
		CK_PROFILE_FUNCTION();
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2{ (float)app.getWindow().getWidth(), (float)app.getWindow().getHeight() };

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* curr_ctx = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(curr_ctx);
		}

		if (ImGuiLayer::fontChange){
			ImGuiLayer::changeFonts();
			ImGuiLayer::fontChange = false;
		}
	}
}
