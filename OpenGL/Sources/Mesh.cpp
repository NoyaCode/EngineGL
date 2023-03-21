#include "Renderer.h"
#include "Mesh.h"

#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>

using namespace LowRenderer;

Mesh::Mesh()
{
}

void Mesh::Update()
{
	Renderer::RenderMesh(this);
}

bool Mesh::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Mesh##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox(("active##" + *id).c_str(), &active);
		ImGui::NewLine();
		ImGui::Text(("Texture :##" + *id).c_str());
		ImGui::Image((ImTextureID) texture->texKey, ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));

	}

	return popUp;
}

