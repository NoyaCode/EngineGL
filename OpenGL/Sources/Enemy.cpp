#include "Enemy.h"
#include "AppState.h"

void Game::Enemy::Init()
{
	target = nullptr;
}

void Game::Enemy::UpdateScript()
{
	if (target)
	{
		UpdateMovements();
	}	
	else if(path.size() > 1)
	{
		target = &path[0];
		forward = (*target - gameObject->transform.position).Normalize();
	}
}

bool Game::Enemy::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Script : Enemy##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox(("active##" + *id).c_str(), &active);
		ImGui::Dummy(ImVec2(10, 10));
		ImGui::Text("\nPath");


		int i = 0;
		if (ImGui::BeginPopupContextItem("DeletePos"))
		{
			if (ImGui::Selectable("Delete"))
			{
				path.erase(path.begin() + i);
			}
			ImGui::EndPopup();
		}
		for (i; i < path.size(); i++)
		{
			ImGui::DragFloat3(("##pos" + *id + std::to_string(i)).c_str(), &path[i].x, 0.1, -100, 100);
			if (ImGui::IsItemClicked(1))
				ImGui::OpenPopup("DeletePos");

		}
		if (ImGui::Button(("+##" + *id).c_str()))
			path.push_back(Vector3());

	}

	return popUp;
}

void Game::Enemy::AddPathPoint(Vector3 point)
{
	path.push_back(point);
}

void Game::Enemy::UpdateMovements()
{
	Vector3 offset = forward * moveSpeed * AppState::deltatime;
	Vector3 targetVector = *target - gameObject->transform.position + offset;

	if (forward.DotProduct(targetVector) <= 0)
	{
		targetId += 1;
		if (targetId < path.size())
		{
			target = &path[targetId];
		}
		else
		{
			targetId = 0;
			target = &path[0];
		}
		forward = (*target - gameObject->transform.position).Normalize();
	}
	else
	{
		gameObject->transform.position += offset;
	}
}
