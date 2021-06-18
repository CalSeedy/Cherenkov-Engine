#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Cherenkov/ImGui/ImGuiLayer.h"

namespace Cherenkov {

	class CK_API Application
	{
		static Application*			s_Instance;

		ImGuiLayer*					m_ImGuiLayer;
		unsigned int				m_IndexBuffer;
		LayerStack					m_LayerStack;
		bool						m_Running = true;
		unsigned int				m_VertexArray;
		unsigned int				m_VertexBuffer;
		std::unique_ptr<Window>		m_Window;

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