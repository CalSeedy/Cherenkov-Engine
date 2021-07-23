#include "ckpch.h"
#include "Cherenkov/Core/Input.h"

#ifdef CK_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsInput.h"
#endif

namespace Cherenkov {
    Scope<Input> Input::s_Instance = Input::Create();
    
    Scope<Input> Input::Create() {
#ifdef CK_PLATFORM_WINDOWS
        return CreateScope<WindowsInput>();
#else
        CK_CORE_ASSERT(false, "Unknown Platform!");
        return nullptr;
#endif
    }
}
