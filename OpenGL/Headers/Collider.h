#pragma once
#include "MyMaths.h"
#include "GameObject.h"
#include "MonoBehaviour.h"
#include "Rigidbody.h"
#include <vector>

using namespace Core::Maths;
using namespace LowRenderer;

namespace Physics
{
	class Collider : public MonoBehaviour
	{
	public:
		virtual Vector3 FindFurthestPoint(Vector3 direction) = 0;
		virtual void ShowCollider(int program) = 0;

		bool show = true;
		bool isTrigger = false;
		bool collide = false;
		Vector3 center;
		Rigidbody* rb;

		void Init();
		void Update() override;
		void Delete() override;

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider(Vector3 _size = Vector3(1, 1, 1));
		bool UpdateComponent(std::string* id) override;
		Vector3 FindFurthestPoint(Vector3 direction) override;
		void ShowCollider(int program) override;
		Vector3 size;
		std::vector<Vector3> vertices;
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider(float _radius = 1);
		bool UpdateComponent(std::string* id) override;
		Vector3 FindFurthestPoint(Vector3 direction) override;
		void ShowCollider(int program) override;
		float radius;
		float scaledRadius;
	};

	class CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider(float _radius = 1, float _height = 1);
		bool UpdateComponent(std::string* id) override;
		Vector3 FindFurthestPoint(Vector3 direction) override;
		void ShowCollider(int program) override;
		float radius;
		float height;

		float scale = 0;
		float hScale = 0;
		Vector3 worldScale = Vector3(1, 1, 1);

		void Init();
		std::vector<Vector3> vertices;
	};
}
