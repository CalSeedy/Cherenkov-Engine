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

		float val1[6] = {
					1.0f, 2.0f, 1.0f, 2.0f, 1.0f, 2.0f
		};
		Cherenkov::Maths::Matrix& mat1 = Cherenkov::Maths::Matrix(3, 2, val1);


		float val2[6] = {
							-1.0f, 3.0f, -1.0f, 3.0f, -1.0f, 3.0f
		};
		Cherenkov::Maths::Matrix& mat2 = Cherenkov::Maths::Matrix(2, 3, val2);


		Cherenkov::Maths::Matrix& mat3 = mat1 + mat2;

		Cherenkov::Maths::Matrix mat4 = mat1 * mat2;
		

		std::cout << mat1 << std::endl;
		std::cout << mat2 << std::endl;
		std::cout << mat3 << std::endl;
		std::cout << mat4 << std::endl;
		PushLayer(new ExampleLayer());

	}

	~Sandbox()
	{
	}
};


Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}