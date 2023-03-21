#include "Camera.h"
#include "Input.h"

using namespace Core;

void Camera::Init(unsigned int width, unsigned int height)
{
	ViewMatrix = gameObject->GetWorldModel().GetInverse();
	ProjectionMatrix = Matrix4::CreatePerspectiveMatrix(0.1, 5000, 90, width, height);
	VP = ProjectionMatrix * ViewMatrix;
}

void Camera::Update()
{
	ViewMatrix = gameObject->GetWorldModel().GetInverse();
	VP = ProjectionMatrix * ViewMatrix;
}

bool LowRenderer::Camera::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Camera##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Text("This is a camera component");
	}

	return popUp;
}
