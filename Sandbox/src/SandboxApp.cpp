#include <Cherenkov.h>
#include "imgui/imgui.h"

class ExampleLayer : public Cherenkov::Layer {

public:
	ExampleLayer() : Layer("Test!") {}

	void onUpdate() override {

		//CK_INFO("Example Layer Updated!");

		if (Cherenkov::Input::isKeyPressed(CK_KEY_TAB)) {
			CK_TRACE("Tab pressed!");
		}
	}

	void onEvent(Cherenkov::Event &event) override {

		CK_TRACE("{0}", event);
	}

	void onImGuiDraw() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
};


class Sandbox : public Cherenkov::Application {

public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};


Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}