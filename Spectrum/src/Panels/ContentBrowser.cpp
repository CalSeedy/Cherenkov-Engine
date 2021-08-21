#include "ckpch.h"
#include "ContentBrowser.h"

#include <unordered_map>
#include <unordered_set>
#include <imgui/imgui.h>

namespace std
{
	template<typename T>
	struct hash<vector<T>>
	{
		typedef vector<T> argument_type;
		typedef std::size_t result_type;
		result_type operator()(argument_type const& in) const
		{
			size_t size = in.size();
			size_t seed = 0;
			for (size_t i = 0; i < size; i++)
				//Combine the hash of the current vector with the hashes of the previous ones
				hash_combine(seed, in[i]);
			return seed;
		}
	};

	template <class T>
	inline void hash_combine(std::size_t& seed, T const& v)
	{
		seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
}



namespace Cherenkov {
	extern const std::filesystem::path g_AssetDir = "assets";


	ContentBrowser::ContentBrowser() : m_CurrentPath{ g_AssetDir } {
		m_CachedPath.emplace_back(g_AssetDir.string());
		m_IconDir = Texture2D::init("resources/icons/folderIcon.png");
		m_IconFile = Texture2D::init("resources/icons/fileIcon.png");
	}

	void ContentBrowser::onImGuiDraw() {
		ImGui::Begin("Content Browser");
		static bool editablePath = false;
		char buff[128] = "";
		strncpy_s(buff, m_CurrentPath.string().c_str(), strlen(m_CurrentPath.string().c_str()));

		if (editablePath) {
			if (ImGui::InputText("##path", buff, sizeof(buff), ImGuiInputTextFlags_EnterReturnsTrue)) {
				
				if (!std::strcmp((std::string(buff)).substr(0, 6).c_str(), g_AssetDir.string().c_str()) && std::filesystem::exists(std::filesystem::path(buff))) m_CurrentPath = buff;

				editablePath = false;
			}
		}
		else {
			int i = 0;
			if (!m_CachedPath.empty()) {
				std::filesystem::path x;
				for (auto& part : m_CachedPath) x /= part;
				if (m_CachedPath.size() != i) i = 0;  for (auto& part : m_CurrentPath) i++; m_CachedPath.resize(i);
				if (x != m_CurrentPath) {
					i = 0;
					for (auto& part : m_CurrentPath) {
						m_CachedPath[i] = part.string();
						i++;
					}
				}
			} else m_CachedPath.emplace_back(g_AssetDir.string());
				

			int c = 0;
			int changePath = -1;
			std::filesystem::path newPath{};
			std::filesystem::path built{};
			for (auto& part : m_CurrentPath) {
				ImGui::PushID(c);
				built /= part;
				auto canonicalPath = std::filesystem::canonical(built);
				std::string txt = m_CachedPath[c];
				ImGui::Button(txt.c_str(), {50.0f, 0});
				if (ImGui::IsItemHovered()) {
					if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
						editablePath = true;
					}
					else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
						changePath = c;
					}
				}
				ImGui::SameLine();

				if (ImGui::Button("/")) ImGui::OpenPopup("Folder select");
				if (ImGui::BeginPopupContextItem("Folder select", ImGuiPopupFlags_MouseButtonLeft)) {
					for (auto& entry : std::filesystem::directory_iterator(built)) {
						if (entry.is_directory()) {
							if (ImGui::MenuItem(entry.path().filename().string().c_str())) {
								changePath = c;
								newPath = built / entry.path().filename();
							}
						}
					}
					ImGui::EndPopup();
				}
				if (c < i -1) ImGui::SameLine();
				ImGui::PopID();
				c++;
			}

			if (changePath > -1) {
				std::filesystem::path tmp;
				int a;
				for (a = 0; a <= changePath; a++) {
					tmp /= m_CachedPath[a];
				}
				m_CurrentPath = tmp;
			}

			if (!newPath.empty()) m_CurrentPath = newPath;
		}

		if (m_CurrentPath != g_AssetDir) {
			if (ImGui::Button("<--")) m_CurrentPath = m_CurrentPath.parent_path();
		}

		ImGui::Separator();

		static float padding = 8.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = 2.0f * padding + thumbnailSize;

		float availableWidth = ImGui::GetContentRegionAvailWidth();
		int  columns = (int)(availableWidth / cellSize);
		if (columns < 1) columns = 1;

		ImGui::Columns(columns);

		for (auto& entry : std::filesystem::directory_iterator(m_CurrentPath)) {
			const std::filesystem::path& path = entry.path();
			std::filesystem::path relPath = std::filesystem::relative(path, g_AssetDir);
			std::string filename = relPath.filename().string();

			const bool isDir = entry.is_directory();
			ImGui::PushID(filename.c_str());
			Ref<Texture2D> icon = isDir ? m_IconDir : m_IconFile;
			ImGui::PushStyleColor(ImGuiCol_Button, { 0,0,0,0 });
			ImGui::ImageButton((ImTextureID)icon->rendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			if (ImGui::BeginDragDropSource()) {

				const wchar_t* payloadPath = relPath.c_str();
				ImGui::SetDragDropPayload("CK_CONTENT_ITEM", payloadPath, (wcslen(payloadPath) + 1)* sizeof(wchar_t), ImGuiCond_Once);
				ImGui::EndDragDropSource();
			}
			ImGui::PopStyleColor();
			
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
				if (isDir)	m_CurrentPath /= path.filename();
				else { 
					m_SelectedFile = m_CurrentPath / relPath.filename();
				}
			}
			ImGui::TextWrapped(filename.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}

}
