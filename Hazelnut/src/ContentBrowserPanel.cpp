#include "hzpch.h"
#include "ContentBrowserPanel.h"

#include <imgui/imgui.h>

namespace Hazel
{
	bool IsImage(const std::filesystem::path& path)
	{
		if (path.has_extension()) {
			if (path.extension() == ".png") return true;
			if (path.extension() == ".jpg") return true;
			if (path.extension() == ".bmp") return true;
		}
		return false;
	}

	extern const std::filesystem::path s_AssetPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		:m_CurrentDirectory(s_AssetPath)
	{
		m_FolderIcon = Texture2D::Create("assets/textures/FolderIcon.png");
		m_FileIcon = Texture2D::Create("assets/textures/FileIcon.png");

		// Loading Textures
		for (auto& directoryEntry : std::filesystem::recursive_directory_iterator(s_AssetPath))
		{
			const auto& path = directoryEntry.path();
			const auto& filenameString = path.string();

			if (IsImage(path))
				m_TextureIcons[filenameString] = Texture2D::Create(filenameString);
		}
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser");

		if (m_CurrentDirectory != s_AssetPath)
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentDirectory = m_CurrentDirectory.parent_path();
			}
		}

		static float padding = 16.0f;//偏移量大小
		static float thumbnailSize = 128.0f;//缩略图大小
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);

		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();//获取it的path对象
			auto relativePath = std::filesystem::relative(path, s_AssetPath);
			std::string filenameString = relativePath.filename().string();

			ImGui::PushID(filenameString.c_str());

			Ref<Texture2D> icon = nullptr;

			if (IsImage(path))
				icon = m_TextureIcons[path.string()];
			else
				icon = directoryEntry.is_directory() ? m_FolderIcon : m_FileIcon;

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));//把按钮的透明的改成0

			//后两个参数是防止图片翻转
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize,thumbnailSize }, { 0,1 }, { 1,0 });

			//发送拖动参数
			if (ImGui::BeginDragDropSource())
			{
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 0, 0, 1));

				int size = static_cast<int>(relativePath.string().length() + 1); // 加 1 是为了包含字符串末尾的 null 字符
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("Content Browser Item", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::Text("%s", filenameString.c_str());

				ImGui::PopStyleColor();
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();

			if (directoryEntry.is_directory() && ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_CurrentDirectory /= path.filename();
			}
			//字体会随着窗口大小调整
			ImGui::TextWrapped(filenameString.c_str());

			ImGui::NextColumn();

			ImGui::PopID();
		}

		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}

}