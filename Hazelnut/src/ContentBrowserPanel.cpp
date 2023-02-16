#include "hzpch.h"
#include "ContentBrowserPanel.h"

#include <imgui/imgui.h>

namespace Hazel
{
	extern const std::filesystem::path s_AssetPath = "assets";

	ContentBrowserPanel::ContentBrowserPanel()
		:m_CurrentDirectory(s_AssetPath)
	{
		m_FolderIcon = Texture2D::Create("assets/textures/FolderIcon.png");
		m_FileIcon = Texture2D::Create("assets/textures/FileIcon.png");
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

		static float padding = 16.0f;//ƫ������С
		static float thumbnailSize = 128.0f;//����ͼ��С
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);

		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			const auto& path = directoryEntry.path();//��ȡit��path����
			auto relativePath = std::filesystem::relative(path, s_AssetPath);
			std::string filenameString = relativePath.filename().string();

			ImGui::PushID(filenameString.c_str());

			Ref<Texture2D> icon = directoryEntry.is_directory() ? m_FolderIcon : m_FileIcon;

			//�����������Ƿ�ֹͼƬ��ת
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize,thumbnailSize }, { 0,1 }, { 1,0 });

			//�����϶�����
			if (ImGui::BeginDragDropSource())
			{
				int size = static_cast<int>(relativePath.string().length() + 1); // �� 1 ��Ϊ�˰����ַ���ĩβ�� null �ַ�
				const wchar_t* itemPath = relativePath.c_str();
				ImGui::SetDragDropPayload("Content Browser Item", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::Text("%s", filenameString.c_str());
				ImGui::EndDragDropSource();
			}

			if (directoryEntry.is_directory() && ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_CurrentDirectory /= path.filename();
			}
			//��������Ŵ��ڴ�С����
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