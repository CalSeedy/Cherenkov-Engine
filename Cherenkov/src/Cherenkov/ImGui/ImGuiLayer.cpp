#include "ckpch.h"
#include "Cherenkov/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Cherenkov/Core/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Cherenkov {
	
	ImGuiLayer::Font ImGuiLayer::font = { "assets/Fonts/Source Sans Pro/SourceSansPro-", 18.0f };
	bool ImGuiLayer::fontChange = false;

	void ImGuiLayer::changeFonts() {
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->Clear();
		if (std::strcmp(ImGuiLayer::font.path.c_str(), "") != 0) {
			io.FontDefault = io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Regular.ttf")).c_str(), ImGuiLayer::font.size);
			io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Bold.ttf")).c_str(), ImGuiLayer::font.size);
			io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("Italic.ttf")).c_str(), ImGuiLayer::font.size);
			io.Fonts->AddFontFromFileTTF((ImGuiLayer::font.path + std::string("BoldItalic.ttf")).c_str(), ImGuiLayer::font.size);
		} else
			io.FontDefault = io.Fonts->AddFontDefault();
		io.Fonts->Build();
		ImGui_ImplOpenGL3_CreateFontsTexture();
	}

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

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
