#pragma once
#include "Input.h"
#include "GameObject.h"
#include "MyMaths.h"
#include "Script.h"
#include "RigidBody.h"
#include "Collider.h"
#include "HeadRotation.h"

using namespace Physics;

using namespace Core::Maths;

namespace Game
{
	class Enemy : public Script
	{
	public:
		void Init() override;
		void UpdateScript() override;
		bool UpdateComponent(std::string* id) override;
		void AddPathPoint(Vector3 point = Vector3());

	private:
		void UpdateMovements();

		std::vector<Vector3> path;
		Vector3 forward;
		float moveSpeed = 3;
		Vector3* target;
		unsigned int targetId = 0;
		float respawnTime = 10;
		float timeToRespawn = 0;
	};
}
