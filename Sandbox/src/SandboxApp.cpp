#include <Cherenkov.h>

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

		//CK_TRACE("{0}", event);
	}
};

class Sandbox : public Cherenkov::Application {

public:
	Sandbox()
	{

		//double data1[16] = {1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, 1};

		Cherenkov::Maths::Matrix mat1 = Cherenkov::Maths::Matrix::Perspective(110, 16 / 9, 2, 100);

		Cherenkov::Maths::Matrix mat1Inv = mat1.Inverse();

		Cherenkov::Maths::Matrix mat2 = mat1.Transpose();


		std::cout << mat1 << std::endl;
		std::cout << "Things: " << mat1.data[3][2] << std::endl;

		std::cout << mat1Inv << std::endl;

		std::cout << mat2 << std::endl;
		std::cout << "Things: " << mat2.data[3][2] << std::endl;

		Cherenkov::Maths::Vector row0 = mat1.getRow(3);
		Cherenkov::Maths::Vector col0 = mat1.getColumn(3);

		double data1[4] = { 2, 2, 2, 2 };
		mat1.setColumn(3, Cherenkov::Maths::Vector(4, data1));
		mat1.setRow(3, Cherenkov::Maths::Vector(4, data1));

		std::cout << mat1 << std::endl;
		std::cout << row0 << std::endl;
		std::cout << col0 << std::endl;


		PushLayer(new ExampleLayer());
		PushOverlay(new Cherenkov::ImGuiLayer());


	}

	~Sandbox()
	{
	}
};




Cherenkov::Application* Cherenkov::createApplication() {
	return new Sandbox();
}