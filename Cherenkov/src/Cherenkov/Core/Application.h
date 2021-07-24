#pragma once
#include "Cherenkov/Core/Core.h"

#include "Cherenkov/Core/Window.h"
#include "Cherenkov/Core/LayerStack.h"
#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Events/ApplicationEvent.h"

#include "Cherenkov/Core/TimeStep.h"

#include "Cherenkov/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Cherenkov {

	class Application
	{
		static Application*				s_Instance;

		float							m_FrameTime = 0.0f;
		ImGuiLayer*						m_ImGuiLayer;
		LayerStack						m_LayerStack;
		bool							m_Running = true;
		bool							m_Minimized = false;
		Scope<Window>					m_Window;

		void run();
		bool onWindowClose(WindowCloseEvent& event);
		bool onWindowResize(WindowResizeEvent& event);

		friend int ::main(int argc, char** argv);
	public:
		Application();
		virtual ~Application();


		void onEvent(Event &event);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static Application& get() { return *s_Instance; }
		inline Window& getWindow() { return *m_Window; }
	};

	Application* createApplication();
}