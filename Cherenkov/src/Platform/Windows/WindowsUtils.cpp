#include "ckpch.h"
#include "Cherenkov/Utils/PlatformUtils.h"

#include "Cherenkov/Core/Application.h"

#include <commdlg.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Cherenkov {

	std::string FileDialogue::open(const char* filter){
		OPENFILENAMEA openfilename;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&openfilename, sizeof(OPENFILENAME));
		openfilename.lStructSize = sizeof(OPENFILENAME);
		openfilename.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().getWindow().getNativeWindow());
		openfilename.lpstrFile = szFile;
		openfilename.nMaxFile = sizeof(szFile);
		openfilename.lpstrFilter = filter;
		openfilename.nFilterIndex = 1;
		openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&openfilename) == TRUE) return openfilename.lpstrFile;

		return std::string();
	}

	std::string FileDialogue::save(const char* filter){
		OPENFILENAMEA openfilename;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&openfilename, sizeof(OPENFILENAME));
		openfilename.lStructSize = sizeof(OPENFILENAME);
		openfilename.hwndOwner = glfwGetWin32Window((GLFWwindow*)Application::get().getWindow().getNativeWindow());
		openfilename.lpstrFile = szFile;
		openfilename.nMaxFile = sizeof(szFile);
		openfilename.lpstrFilter = filter;
		openfilename.nFilterIndex = 1;
		openfilename.lpstrDefExt = std::strchr(filter, '\0') + 1;
		openfilename.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetSaveFileNameA(&openfilename) == TRUE) return openfilename.lpstrFile;

		return std::string();
	}
}
