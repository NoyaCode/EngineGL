#include "MonoBehaviour.h"
#include "GameObject.h"


bool LowRenderer::MonoBehaviour::IsActive(bool onlyGO)
{
	if (!active && !onlyGO)
		return false;

	Graph* o = gameObject->node;
	while (o != nullptr)
	{
		if (o->object->active)
			o = o->parent;
		else
			return false;
	}
	return true;
}

void LowRenderer::MonoBehaviour::UpdateInspector(int index)
{
	std::string id = std::to_string(index);
	if (UpdateComponent(&id))
	{
		ImGui::OpenPopup(("ComponentMenu##" + id).c_str());
	}

	if (ImGui::BeginPopupContextItem(("ComponentMenu##" + id).c_str()))
	{
		if (ImGui::Selectable("Delete"))
		{
			Delete();
			gameObject->DeleteComponent(this);
		}
		ImGui::EndPopup();
	}
}