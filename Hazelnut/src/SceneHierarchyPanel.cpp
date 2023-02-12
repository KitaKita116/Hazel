#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include "Hazel/Scene/Components.h"
#include <imgui/imgui_internal.h>

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
		//按下鼠标左键且在窗口上
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		//弹出窗口
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}


		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
			//如果按钮被点击
			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");
			//控制弹出的窗口
			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite Renderer"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}
		}
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

		bool entityDeleted = false;
		//用于创建一个上下文弹出窗口，该窗口将与当前选定的 UI 元素相关联。
		//这意味着，如果鼠标当前位于某个 UI 元素上，则该弹出窗口将出现在该 UI 元素附近。
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		//用来使id唯一，防止多个控件被同时控制
		ImGui::PushID(label.c_str());

		//创建两列
		ImGui::Columns(2);
		//设置第0列的宽
		ImGui::SetColumnWidth(0, columnWidth);
		//显示文本
		ImGui::Text(label.c_str());
		//转到下一列
		ImGui::NextColumn();
		//创建多个项目的宽度数组，其中每个项目的宽度相同。
		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		//设置项目间距为0
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
		//计算行高
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		//设置按钮大小
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		//设置X参数
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		// "##"表示隐藏
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		//设置Y参数
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();
		//设置Z参数
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		//ImGuiTreeNodeFlags_DefaultOpen 标志表示该节点的子节点将默认打开，即显示其内容。
		//ImGuiTreeNodeFlags_AllowItemOverlap 标志表示该节点允许与其他 UI 元素重叠
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

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
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), treeNodeFlags, "Transform"))
			{
				auto& tc = entity.GetComponent<TransformComponent>();
				DrawVec3Control("Translation", tc.Translation);
				glm::vec3 rotation = glm::degrees(tc.Rotation);
				DrawVec3Control("Rotation", rotation);
				tc.Rotation = glm::radians(rotation);
				DrawVec3Control("Scale", tc.Scale, 1.0f);

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), treeNodeFlags, "Camera"))
			{
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.Camera;

				ImGui::Checkbox("Primary", &cameraComponent.Primary);

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
				ImGui::Text("Projection"); ImGui::SameLine();
				//返回值为下拉列表是否打开
				if (ImGui::BeginCombo(" ", currentProjectionTypeString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
						//如果被选中
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionTypeString = projectionTypeStrings[i];
							camera.SetProjectionType((SceneCamera::ProjectionType)i);
						}

						if (isSelected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
				{
					float verticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
					if (ImGui::DragFloat("Vertical FOV", &verticalFov))
						camera.SetPerspectiveVerticalFOV(glm::radians(verticalFov));

					float orthoNear = camera.GetPerspectiveNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetPerspectiveNearClip(orthoNear);

					float orthoFar = camera.GetPerspectiveFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetPerspectiveFarClip(orthoFar);
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
				{
					float orthoSize = camera.GetOrthographicSize();
					if (ImGui::DragFloat("Size", &orthoSize))
						camera.SetOrthographicSize(orthoSize);

					float orthoNear = camera.GetOrthographicNearClip();
					if (ImGui::DragFloat("Near", &orthoNear))
						camera.SetOrthographicNearClip(orthoNear);

					float orthoFar = camera.GetOrthographicFarClip();
					if (ImGui::DragFloat("Far", &orthoFar))
						camera.SetOrthographicFarClip(orthoFar);

					ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.FixedAspectRatio);
				}

				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			//ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			bool open = ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), treeNodeFlags, "Sprite Renderer");
			ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
			if (ImGui::Button("+", ImVec2{ 20, 20 }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
			//ImGui::PopStyleVar();

			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				auto& src = entity.GetComponent<SpriteRendererComponent>();
				ImGui::ColorEdit4("Color", glm::value_ptr(src.Color));
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<SpriteRendererComponent>();
		}
	}
}