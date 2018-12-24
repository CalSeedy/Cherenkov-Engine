#pragma once

#ifdef CK_PLATFORM_WINDOWS

extern Cherenkov::Application* Cherenkov::createApplication();

int main(int argc, char** argv) {
	Cherenkov::Log::init();
	CK_CORE_INFO("Log initialised!");
	int a = 5;
	CK_ERROR("...Log initialised! = {0}", 5);

	auto app = Cherenkov::createApplication();
	app->Run();
	delete app;
}

#endif