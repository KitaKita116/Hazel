#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
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

		//������ÿ��entity��id
		m_Context->m_Registry.each([&](auto entityID)
			{
				//�����entity
				Entity e(entityID, m_Context.get());
				DrawEntityNode(e);
			}

		);
		//�������������ڴ�����
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};
		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);

		ImGui::End();
	}
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		//ImGuiTreeNodeFlags_OpenOnArrow ��������������־λ����ôֻ�е����ͷ�Ż�չ������Ľڵ�
		//ImGuiTreeNodeFlags_Selected	 ��������������־λ����ô�ڵ�ѡ�������ɫ
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		//����ֵ������ǰ���ڵ��Ƿ񱻴�
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

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());

			ImGui::Text("Tag");
			ImGui::SameLine();

			if (ImGui::InputText(" ", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::Text("Position");
				ImGui::SameLine();
				ImGui::DragFloat3(" ", glm::value_ptr(transform[3]), 0.1f);

				ImGui::TreePop();
			}
		}
	}
}