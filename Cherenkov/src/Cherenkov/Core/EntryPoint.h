#pragma once
#include "Cherenkov/Core/Core.h"
#include "Cherenkov/Core/Application.h"

#ifdef CK_PLATFORM_WINDOWS

extern Cherenkov::Application* Cherenkov::createApplication(AppCommandlineArgs args);

int main(int argc, char** argv) {
	Cherenkov::Log::init();
	CK_PROFILE_BEGIN("Startup", "profiling-startup.json");
	auto app = Cherenkov::createApplication({argc, argv});
	CK_PROFILE_END();
	CK_PROFILE_BEGIN("Runtime", "profiling-runtime.json");
	app->run();
	CK_PROFILE_END();
	CK_PROFILE_BEGIN("Shutdown", "profiling-shutdown.json");
	delete app;
	CK_PROFILE_END();
}

#endif
