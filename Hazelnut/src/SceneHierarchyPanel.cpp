#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>
#include "Hazel/Scene/Components.h"

namespace Hazel
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& contex)
	{
		SetContext(contex);
	}
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& contex)
	{
		m_Context = contex;
	}
	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		//参数是每个entity的id
		m_Context->m_Registry.each([&](auto entityID)
			{
				//构造该entity
				Entity e(entityID, m_Context.get());
				DrawEntityNode(e);
			}
		);

		ImGui::End();
	}
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		//ImGuiTreeNodeFlags_OpenOnArrow 如果设置了这个标志位，那么只有点击箭头才会展开下面的节点
		//ImGuiTreeNodeFlags_Selected	 如果设置了这个标志位，那么节点选择会有颜色
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		//返回值表明当前树节点是否被打开
		bool opened = ImGui::TreeNodeEx((void*)entity.getEntityID(), flags, tag.c_str());
		
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
	}
}