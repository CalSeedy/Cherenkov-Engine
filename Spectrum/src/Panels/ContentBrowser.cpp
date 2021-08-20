#include "ckpch.h"
#include "ContentBrowser.h"

#include <imgui/imgui.h>

namespace Cherenkov {
	
	ContentBrowser::ContentBrowser() {
		m_IconDir = Texture2D::init("resources/icons/folderIcon.png");
		m_IconFile = Texture2D::init("resources/icons/fileIcon.png");
	}

	void ContentBrowser::onImGuiDraw() {
		ImGui::Begin("Content Browser");
		ImGui::Text("%s", m_CurrentPath.string().c_str());

		if (m_CurrentPath != m_AssetDir) {
			if (ImGui::Button("<--")) m_CurrentPath = m_CurrentPath.parent_path();
		}

		static float padding = 8.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = 2.0f * padding + thumbnailSize;

		float availableWidth = ImGui::GetContentRegionAvailWidth();
		int  columns = (int)(availableWidth / cellSize);
		if (columns < 1) columns = 1;

		ImGui::Columns(columns);

		for (auto& entry : std::filesystem::directory_iterator(m_CurrentPath)) {
			const std::filesystem::path& path = entry.path();
			std::filesystem::path relPath = std::filesystem::relative(path, m_AssetDir);
			std::string filename = relPath.filename().string();

			const bool isDir = entry.is_directory();

			Ref<Texture2D> icon = isDir ? m_IconDir : m_IconFile;

			ImGui::ImageButton((ImTextureID)icon->rendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
				if (isDir)	m_CurrentPath /= path.filename();
				else { 
					auto txt = (m_CurrentPath / relPath.filename()).string();
					CK_CORE_WARN("{0} selected!", txt.c_str());
				}
			}
			ImGui::TextWrapped(filename.c_str());

			ImGui::NextColumn();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}

}
