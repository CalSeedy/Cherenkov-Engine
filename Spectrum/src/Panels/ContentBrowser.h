#pragma once
#include "Cherenkov/Renderer/Texture.h"

namespace Cherenkov {

	class ContentBrowser {
		const std::filesystem::path m_AssetDir = std::filesystem::path("assets");
		std::filesystem::path		m_CurrentPath{m_AssetDir};
		std::filesystem::path		m_SelectedFile{""};

		Ref<Texture2D>				m_IconDir;
		Ref<Texture2D>				m_IconFile;
		
	public:
		ContentBrowser();

		void onImGuiDraw();

	};
}
