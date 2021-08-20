#pragma once
#include "Cherenkov/Renderer/Texture.h"

namespace Cherenkov {

	class ContentBrowser {
		std::filesystem::path		m_CurrentPath;
		std::filesystem::path		m_SelectedFile{""};

		Ref<Texture2D>				m_IconDir;
		Ref<Texture2D>				m_IconFile;
		
	public:
		ContentBrowser();

		void onImGuiDraw();

	};
}
