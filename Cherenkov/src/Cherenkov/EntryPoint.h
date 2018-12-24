#pragma once

#ifdef CK_PLATFORM_WINDOWS

extern Cherenkov::Application* Cherenkov::createApplication();

int main(int argc, char** argv) {

	auto app = Cherenkov::createApplication();
	app->Run();
	delete app;
}

#endif