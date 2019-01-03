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

		double data1[16] = {1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1};

		Cherenkov::Maths::Matrix mat1 = Cherenkov::Maths::Matrix(4, 4, data1);

		Cherenkov::Maths::Matrix mat1Inv = mat1.Inverse();

		std::cout << mat1 << std::endl;
		std::cout << mat1Inv << std::endl;


		PushLayer(new ExampleLayer());



	}

	~Sandbox()
	{
	}
};


	

Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}