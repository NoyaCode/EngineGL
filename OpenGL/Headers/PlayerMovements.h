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
	class PlayerMovements : public Script
	{
	public:
		void Init() override;
		void UpdateScript() override;
		bool UpdateComponent(std::string* id) override;
		void ResetPos();
		Rigidbody* rb;
		BoxCollider* groundCheck;
		
	private:
		void UpdateRotation();
		void UpdateMovements();

		Vector3 forward;
		Vector3 Up = Vector3(0, 1, 0);

		float moveSpeed = 300;
		float jumpForce = 10;
		float rotationSpeed = 10;
		bool grounded = false;
		bool jumped = false;

		double lastCursorX = NULL;
	};
}
