#include "HeadRotation.h"

using namespace Game;
using namespace Core;

void HeadRotation::UpdateScript()
{
	UpdateRotation();
}

bool HeadRotation::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Script : HeadRotation##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox(("active##" + *id).c_str(), &active);
	}

	return popUp;
}

void HeadRotation::UpdateRotation()
{
	if (Input::mousePos.y == lastCursorY) return;
	else if (lastCursorY == NULL) { lastCursorY = Input::mousePos.y; return; }

	float yoffset = lastCursorY - Input::mousePos.y;
	lastCursorY = Input::mousePos.y;

	float sensitivity = 0.1f;
	yoffset *= sensitivity;

	gameObject->transform.rotation.x -= yoffset;

	if (gameObject->transform.rotation.x > 89.0f)
		gameObject->transform.rotation.x = 89.0f;
	if (gameObject->transform.rotation.x < -89.0f)
		gameObject->transform.rotation.x = -89.0f;
}
