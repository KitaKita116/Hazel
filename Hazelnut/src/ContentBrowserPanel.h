#pragma once

#include <filesystem>
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_FolderIcon;
		Ref<Texture2D> m_FileIcon;
	};

}