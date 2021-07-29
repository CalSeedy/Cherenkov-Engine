#include <Cherenkov.h>
#include <Cherenkov/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Cherenkov {
	class Editor : public Application {
	public:
		Editor() : Application("Spectrum") {
			//PushLayer(new ExampleLayer());
			pushLayer(new EditorLayer());
		}

		~Editor() {}
	};

	Application* createApplication() {
		return new Editor();
	}
}