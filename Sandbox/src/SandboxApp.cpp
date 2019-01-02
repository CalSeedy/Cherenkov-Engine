#include <Cherenkov.h>

class ExampleLayer : public Cherenkov::Layer {

public:
	ExampleLayer() : Layer("Test!") {}

	void onUpdate() override {
	
		//CK_INFO("Example Layer Updated!");
	}

	void onEvent(Cherenkov::Event &event) override {

		CK_TRACE("{0}", event);
	}
};


class Sandbox : public Cherenkov::Application {

public:
	Sandbox()
	{
		
		float data1[9] = { 1.0f, 0.0f, 2.0f, 1.0f, 3.0f, 4.0f, 0.0f, 6.0f, 0.0f};

		Cherenkov::Maths::Matrix mat1 = Cherenkov::Maths::Matrix(3, 3, data1);
		float det = mat1.Det();
		std::cout << mat1 << std::endl << "Determinant: " << det << std::endl;

		PushLayer(new ExampleLayer());

	}

	~Sandbox()
	{
	}
};


Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}