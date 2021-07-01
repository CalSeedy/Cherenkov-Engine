#pragma once

#ifdef CK_PLATFORM_WINDOWS

extern Cherenkov::Application* Cherenkov::createApplication();

int main(int argc, char** argv) {
	Cherenkov::Log::init();
	CK_CORE_INFO("Log initialised!");
	auto app = Cherenkov::createApplication();
	app->Run();
	delete app;
}

#endif