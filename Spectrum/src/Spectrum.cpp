#include <Cherenkov.h>
#include <Cherenkov/Core/EntryPoint.h>

#include "EditorLayer.h"

// testing whether EnTT was added successfully
#include <entt/entt.hpp>

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