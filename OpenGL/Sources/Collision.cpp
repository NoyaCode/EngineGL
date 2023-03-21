#include "Collision.h"
#include "Debug.h"
#include "PlayerMovements.h"
#include "AppState.h"

using namespace Physics;

void Collision::UpdateCollisions()
{
	std::vector<Collider*> activeColliders;
	std::vector<Rigidbody*> rigidbodies;
	for (Collider* collider : currentColliders)
	{
		collider->collide = false;
		if (collider->IsActive())
		{
			activeColliders.push_back(collider);
			if (collider->rb)
				rigidbodies.push_back(collider->rb);
		}
	}

	for (unsigned int A = 0; A < activeColliders.size(); A++)
	{
		for (unsigned int B = A + 1; B < activeColliders.size(); B++)
		{
			if (activeColliders[A]->gameObject == activeColliders[B]->gameObject)
				continue;
			if (!activeColliders[A]->rb && !activeColliders[B]->rb)
				continue;

			Vector3 offsetA = activeColliders[A]->rb ? (activeColliders[A]->rb->velocity) * AppState::deltatime : Vector3();
			Vector3 offsetB = activeColliders[B]->rb ? (activeColliders[B]->rb->velocity) * AppState::deltatime : Vector3();
			activeColliders[A]->gameObject->transform.position += offsetA;
			activeColliders[B]->gameObject->transform.position += offsetB;

			CollisionInfo info = CollisionDetection(activeColliders[A], activeColliders[B]);
			if (info.hasCollision) // Collision detected
			{
				activeColliders[A]->collide = true;
				activeColliders[B]->collide = true;

				bool breakIfStatement = false;
				if (AppState::sceneMode == AppState::Mode::EDITOR || activeColliders[A]->isTrigger || activeColliders[B]->isTrigger)
					breakIfStatement = true;

				if (!breakIfStatement)
				{
					if (activeColliders[A]->rb && activeColliders[B]->rb) // Both colliders have a Rigidbody
					{
						activeColliders[A]->rb->velocity -= (info.normal * info.depth * 0.5f) / AppState::deltatime;
						activeColliders[B]->rb->velocity += (info.normal * info.depth * 0.5f) / AppState::deltatime;

						activeColliders[A]->rb->reset = true;
						activeColliders[B]->rb->reset = true;
					}
					if (activeColliders[A]->rb) // Only collider A has a Rigidbody
					{
						activeColliders[A]->rb->velocity -= (info.normal * info.depth) / AppState::deltatime;
						activeColliders[A]->rb->reset = true;
					}
					else  // Only collider B has a Rigidbody
					{
						activeColliders[B]->rb->velocity += (info.normal * info.depth) / AppState::deltatime;
						activeColliders[B]->rb->reset = true;
					}

					if (activeColliders[A]->gameObject->layer == Layer::PLAYER && activeColliders[B]->gameObject->layer == Layer::ENEMY)
					{
						if (info.normal.DotProduct(Vector3(0, -1, 0)) > 0.4)
							activeColliders[B]->gameObject->active = false;
						else
							activeColliders[A]->gameObject->GetComponent<Game::PlayerMovements>()->ResetPos();
					}
					else if (activeColliders[B]->gameObject->layer == Layer::PLAYER && activeColliders[A]->gameObject->layer == Layer::ENEMY)
					{
						if (info.normal.DotProduct(Vector3(0, 1, 0)) > 0.4)
							activeColliders[A]->gameObject->active = false;
						else
							activeColliders[B]->gameObject->GetComponent<Game::PlayerMovements>()->ResetPos();
					}
				}
			}
			if(activeColliders[A]->gameObject)
				activeColliders[A]->gameObject->transform.position -= offsetA;
			if (activeColliders[B]->gameObject)
				activeColliders[B]->gameObject->transform.position -= offsetB;
		}
	}
	if (AppState::sceneMode == AppState::Mode::EDITOR)
		return;
	for (Rigidbody* rb : rigidbodies)
	{
		rb->gameObject->transform.position += rb->velocity * AppState::deltatime;
		if (rb->reset)
		{
			//rb->velocity.y = 0;
			rb->velocity = Vector3();
			rb->reset = false;
		}

	}
}

Collision::CollisionInfo Collision::CollisionDetection(Collider* colliderA, Collider* colliderB)
{
	CollisionInfo info;
	info.depth = 0;
	info.hasCollision = false;

	if (typeid(*colliderA) == typeid(SphereCollider) && typeid(*colliderB) == typeid(SphereCollider)) //collisions shphere-sphere
	{
		Vector3 posA = (colliderA->gameObject->GetWorldModel() * Vector4(colliderA->center, 1)).xyz;
		Vector3 posB = (colliderB->gameObject->GetWorldModel() * Vector4(colliderB->center, 1)).xyz;

		SphereCollider* sphereA = (SphereCollider*)colliderA;
		SphereCollider* sphereB = (SphereCollider*)colliderB;

		Vector3 centerCenter = posB - posA;

		float distance = centerCenter.GetMagnitude();

		float radiusAdded = sphereA->scaledRadius + sphereB->scaledRadius;

		if (distance < radiusAdded)
		{
			info.depth = radiusAdded - distance;
			info.normal = centerCenter.Normalize();
			info.hasCollision = true;
			return info;
		}
		return info;
	}

	Vector3 support = Support(colliderA, colliderB, Vector3(0, 1, 0));

	std::vector<Vector3> simplex;
	simplex.insert(simplex.begin(), support);

	Vector3 direction = -1 * support;

	int index = 0;
	while (index < 50)
	{
		support = Support(colliderA, colliderB, direction);

		if (support.DotProduct(direction) <= 0)
		{
			return info;
		}

		simplex.insert(simplex.begin(), support);
		if (NextSimplex(simplex, direction))
		{
			info = GetCollisionInfo(simplex, *colliderA, *colliderB);
			return info;
		}
		index++;
	}
	return info;
}

Vector3 Collision::Support(Collider* colliderA, Collider* colliderB, Vector3 direction)
{
	return colliderA->FindFurthestPoint(direction) - colliderB->FindFurthestPoint(-1 * direction);
}

bool Collision::NextSimplex(std::vector<Vector3>& simplex, Vector3& direction)
{
	switch (simplex.size())
	{
	case 2: return Line(simplex, direction);
	case 3: return Triangle(simplex, direction);
	case 4: return Tetrahedron(simplex, direction);
	}

	return false;
}

bool Collision::SameDirection(const Vector3& direction, const Vector3& ao)
{
	return direction.DotProduct(ao) > 0;
}

bool Collision::Line(std::vector<Vector3>& simplex, Vector3& direction)
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];

	Vector3 ab = b - a;
	Vector3 ao = -1 * a;

	if (SameDirection(ab, ao))
	{
		direction = ab.CrossProduct(ao).CrossProduct(ab);
	}

	else
	{
		simplex = { a };
		direction = ao;
	}

	return false;
}

bool Collision::Triangle(std::vector<Vector3>& simplex, Vector3& direction)
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];
	Vector3 c = simplex[2];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ao = -1 * a;

	Vector3 abc = ab.CrossProduct(ac);

	if (SameDirection(abc.CrossProduct(ac), ao))
	{
		if (SameDirection(ac, ao))
		{
			simplex = { a, c };
			direction = ac.CrossProduct(ao).CrossProduct(ac);
		}

		else
		{
			return Line(simplex = { a, b }, direction);
		}
	}

	else
	{
		if (SameDirection(ab.CrossProduct(abc), ao))
		{
			return Line(simplex = { a, b }, direction);
		}

		else
		{
			if (SameDirection(abc, ao))
			{
				direction = abc;
			}

			else
			{
				simplex = { a, c, b };
				direction = -1 * abc;
			}
		}
	}

	return false;
}

bool Collision::Tetrahedron(std::vector<Vector3>& simplex, Vector3& direction)
{
	Vector3 a = simplex[0];
	Vector3 b = simplex[1];
	Vector3 c = simplex[2];
	Vector3 d = simplex[3];

	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 ad = d - a;
	Vector3 ao = -1 * a;

	Vector3 abc = ab.CrossProduct(ac);
	Vector3 acd = ac.CrossProduct(ad);
	Vector3 adb = ad.CrossProduct(ab);

	if (SameDirection(abc, ao))
		return Triangle(simplex = { a, b, c }, direction);

	if (SameDirection(acd, ao))
		return Triangle(simplex = { a, c, d }, direction);

	if (SameDirection(adb, ao))
		return Triangle(simplex = { a, d, b }, direction);

	return true;
}


std::pair<std::vector<Vector4>, size_t> Collision::GetFaceNormals(const std::vector<Vector3>& polytope, const std::vector<size_t>& faces)
{
	std::vector<Vector4> normals;
	size_t minTriangle = 0;
	float  minDistance = FLT_MAX;

	for (size_t i = 0; i < faces.size(); i += 3)
	{
		Vector3 a = polytope[faces[i]];
		Vector3 b = polytope[faces[i + 1]];
		Vector3 c = polytope[faces[i + 2]];

		Vector3 normal = ((b - a).CrossProduct(c - a)).Normalize();
		float distance = normal.DotProduct(a);

		if (distance < 0)
		{
			normal *= -1;
			distance *= -1;
		}

		normals.emplace_back(normal, distance);

		if (distance < minDistance)
		{
			minTriangle = i / 3;
			minDistance = distance;
		}
	}

	return { normals, minTriangle };
}

void Collision::AddIfUniqueEdge(std::vector<std::pair<size_t, size_t>>& edges, const std::vector<size_t>& faces, size_t a, size_t b)
{
	auto reverse = std::find(edges.begin(), edges.end(), std::make_pair(faces[b], faces[a]));

	if (reverse != edges.end())
		edges.erase(reverse);
	else
		edges.emplace_back(faces[a], faces[b]);
}

Collision::CollisionInfo Collision::GetCollisionInfo(std::vector<Vector3> simplex, Collider& c1, Collider& c2) // Finish and understand
{
	std::vector<Vector3> polytope(simplex.begin(), simplex.end());
	std::vector<size_t>  faces = {
		0, 1, 2,
		0, 3, 1,
		0, 2, 3,
		1, 3, 2
	};

	auto [normals, minFace] = GetFaceNormals(polytope, faces);
	if (normals.size() <= 0)
	{
		CollisionInfo info;

		info.normal = Vector3();
		info.depth = 0;
		info.hasCollision = true;

		return info;
	}
	Vector3 minNormal;
	float   minDistance = FLT_MAX;

	int loopIndex = 0;
	while (minDistance == FLT_MAX) 
	{
		minNormal = normals[minFace].xyz;
		minDistance = normals[minFace].w;

		Vector3 support = Support(&c1, &c2, minNormal);
		float sDistance = minNormal.DotProduct(support);
		float test = abs(sDistance - minDistance);

		loopIndex++;
		if (loopIndex > 50) // avoid infinite loops
		{
			CollisionInfo info;
			info.normal = minNormal;
			info.depth = minDistance;
			info.hasCollision = true;
			return info;
		}

		if (abs(sDistance - minDistance) > 0.001f) 
		{
			minDistance = FLT_MAX;

			std::vector<std::pair<size_t, size_t>> uniqueEdges;

			for (size_t i = 0; i < normals.size(); i++) 
			{
				if (normals[i].xyz.DotProduct(support) > 0) 
				{
					size_t f = i * 3;

					AddIfUniqueEdge(uniqueEdges, faces, f, f + 1);
					AddIfUniqueEdge(uniqueEdges, faces, f + 1, f + 2);
					AddIfUniqueEdge(uniqueEdges, faces, f + 2, f);

					faces[f + 2] = faces.back(); faces.pop_back();
					faces[f + 1] = faces.back(); faces.pop_back();
					faces[f] = faces.back(); faces.pop_back();

					normals[i] = normals.back(); normals.pop_back();

					i--;
				}
			}
			std::vector<size_t> newFaces;
			for (auto [edgeIndex1, edgeIndex2] : uniqueEdges) 
			{
				newFaces.push_back(edgeIndex1);
				newFaces.push_back(edgeIndex2);
				newFaces.push_back(polytope.size());
			}

			polytope.push_back(support);

			auto [newNormals, newMinFace] = GetFaceNormals(polytope, newFaces);
			if (normals.size() <= 0)
			{
				CollisionInfo info;
				info.normal = Vector3();
				info.depth = 0;
				info.hasCollision = true;
				return info;
			}

			float oldMinDistance = FLT_MAX;
			for (size_t i = 0; i < normals.size(); i++) 
			{
				if (normals[i].w < oldMinDistance) 
				{
					oldMinDistance = normals[i].w;
					minFace = i;
				}
			}

			if (newMinFace < newNormals.size() && newNormals[newMinFace].w < oldMinDistance) 
				minFace = newMinFace + normals.size();


			faces.insert(faces.end(), newFaces.begin(), newFaces.end());
			normals.insert(normals.end(), newNormals.begin(), newNormals.end());
		}

	}
	CollisionInfo info;

	info.normal = minNormal;
	info.depth = minDistance + 0.001f;
	info.hasCollision = true;

	return info;
}