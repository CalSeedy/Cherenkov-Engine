#pragma once

#include "Cherenkov/core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Cherenkov/ImGui/ImGuiLayer.h"
#include "Cherenkov/Renderer/Buffer.h"
#include "Cherenkov/Renderer/Renderer.h"
#include "Cherenkov/Renderer/Shader.h"
#include "Cherenkov/Renderer/VertexArray.h"

namespace Cherenkov {

	class CK_API Application
	{
		static Application*				s_Instance;

		ImGuiLayer*						m_ImGuiLayer;
		LayerStack						m_LayerStack;
		bool							m_Running = true;
		std::shared_ptr<Shader>			m_Shader;
		std::shared_ptr<VertexArray>	m_VertexArray;
		std::shared_ptr<Window>			m_Window;

		bool onWindowClose(WindowCloseEvent& event);
	public:
		Application();
		virtual ~Application();

		void Run();

		void onEvent(Event &event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	};

	Application* createApplication();
}