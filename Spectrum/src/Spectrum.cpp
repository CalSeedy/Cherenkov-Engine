#include <Cherenkov.h>
#include <Cherenkov/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Cherenkov {
	class Spectrum : public Application {
	public:
		Spectrum(AppCommandlineArgs args) : Application("Spectrum", args) {
			//PushLayer(new ExampleLayer());
			pushLayer(new EditorLayer());
		}

		~Spectrum() {}
	};

	Application* createApplication(AppCommandlineArgs args) {
		return new Spectrum(args);
	}
}
