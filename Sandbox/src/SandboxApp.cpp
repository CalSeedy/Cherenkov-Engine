#include <Cherenkov.h>
#include <Cherenkov/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Cherenkov::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {}
};

Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}