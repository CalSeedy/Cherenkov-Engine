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
		
		float data[9];
		for (int i = 0; i < 9;  ++i) {
			data[i] = i + 1;
		}

		Cherenkov::Maths::Matrix mat1 = Cherenkov::Maths::Matrix(3, 3, data);


		float data2[3] = { 1, 2, 3 };
		Cherenkov::Maths::Matrix mat2 = Cherenkov::Maths::Matrix(1, 3, data2);
		
		
		Cherenkov::Maths::Matrix mat3 = mat2 * mat1;


		float dotpro = mat2.Dot(mat1);

		std::cout << mat1 << std::endl;
		std::cout << mat2 << std::endl;
		std::cout << mat3 << std::endl;

		std::cout << "^mat1^ dot ^mat2^ = " << dotpro << std::endl;
		PushLayer(new ExampleLayer());

	}

	~Sandbox()
	{
	}
};


Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}