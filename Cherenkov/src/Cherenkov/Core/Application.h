#pragma once

#include "Cherenkov/Core/Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Events/ApplicationEvent.h"

#include "Cherenkov/Core/TimeStep.h"

#include "Cherenkov/ImGui/ImGuiLayer.h"

#include "Cherenkov/Renderer/Buffer.h"
#include "Cherenkov/Renderer/Camera.h"
#include "Cherenkov/Renderer/Shader.h"
#include "Cherenkov/Renderer/VertexArray.h"

namespace Cherenkov {

	class CK_API Application
	{
		static Application*				s_Instance;

		float							m_FrameTime = 0.0f;
		ImGuiLayer*						m_ImGuiLayer;
		LayerStack						m_LayerStack;
		bool							m_Running = true;
		bool							m_Minimized = false;
		Scope<Window>					m_Window;

		bool onWindowClose(WindowCloseEvent& event);
		bool onWindowResize(WindowResizeEvent& event);
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