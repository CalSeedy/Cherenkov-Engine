#pragma once
#include "Cherenkov/Core/Core.h"

#include "Cherenkov/Core/Window.h"
#include "Cherenkov/Core/LayerStack.h"
#include "Cherenkov/Events/Event.h"
#include "Cherenkov/Events/ApplicationEvent.h"

#include "Cherenkov/Core/TimeStep.h"

#include "Cherenkov/ImGui/ImGuiLayer.h"
#include "Debug/Assert.h"

int main(int argc, char** argv);

namespace Cherenkov {

	struct AppCommandlineArgs {
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const {
			CK_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	class Application
	{
		static Application*				s_Instance;

		AppCommandlineArgs				m_CommandlineArgs;
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
		Application(const std::string& title = "Cherenkov App");
		Application(const std::string& title = "Cherenkov App", AppCommandlineArgs args = AppCommandlineArgs());
		virtual ~Application();

		void onEvent(Event &event);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		static Application& get() { return *s_Instance; }
		ImGuiLayer* getImGuiLayer() { return m_ImGuiLayer; }
		Window& getWindow() { return *m_Window; }
		AppCommandlineArgs getCommandlineArgs() const { return m_CommandlineArgs; }

		void close();
	};

	Application* createApplication();
	Application* createApplication(AppCommandlineArgs args);
}
