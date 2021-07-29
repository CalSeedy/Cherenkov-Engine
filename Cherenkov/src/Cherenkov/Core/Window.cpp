#include "ckpch.h"
#include "Cherenkov/Core/Window.h"

#ifdef CK_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Cherenkov {
	
	Scope<Window> Window::Create(const WindowProperties& properties) {
#ifdef CK_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(properties);
#else
		CK_CORE_ASSERT(false, "Unknown Platform!");
		return nullptr;
#endif
	}
}
