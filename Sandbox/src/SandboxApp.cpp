#include "ckpch.h"
#include "Cherenkov.h"

class Sandbox : public Cherenkov::Application {

public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};


Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}