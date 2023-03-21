#pragma once
#include "Collider.h"
#include <array>
#include <vector>

namespace Physics
{
	static class Collision
	{
	public:
		struct CollisionInfo
		{
			Vector3 A;
			Vector3 B;
			Vector3 normal;
			float depth = 0;
			bool hasCollision = false;
		};

		static void UpdateCollisions();
		static CollisionInfo CollisionDetection(Collider* colliderA, Collider* colliderB);
		inline static std::vector<Collider*> currentColliders;
	private:
		static Vector3 Support(Collider* colliderA, Collider* colliderB, Vector3 direction);
		static bool NextSimplex(std::vector<Vector3>& simplex, Vector3& direction);
		static bool SameDirection(const Vector3& direction, const Vector3& ao);
		static bool Line(std::vector<Vector3>& simplex, Vector3& direction);
		static bool Triangle(std::vector<Vector3>& simplex, Vector3& direction);
		static bool Tetrahedron(std::vector<Vector3>& simplex, Vector3& direction);

		static CollisionInfo GetCollisionInfo(std::vector<Vector3> simplex, Collider& colliderA, Collider& colliderB);
		static std::pair<std::vector<Vector4>, size_t> GetFaceNormals(const std::vector<Vector3>& polytope, const std::vector<size_t>& faces);
		static void AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a, size_t b);
	};
}