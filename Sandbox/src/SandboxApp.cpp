#include <Cherenkov.h>
#include <Cherenkov/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Cherenkov::Application {
public:
	Sandbox(Cherenkov::AppCommandlineArgs args) : Cherenkov::Application("Sandbox", args) {
		//PushLayer(new ExampleLayer());
		pushLayer(new Sandbox2D());
	}

	~Sandbox() {}
};

Cherenkov::Application* Cherenkov::createApplication(Cherenkov::AppCommandlineArgs args) {
	return new Sandbox(args);
}
