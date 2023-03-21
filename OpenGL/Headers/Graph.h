#pragma once
#include <list>;

namespace Core
{
	class GameObject;
}

using namespace Core;

namespace DataStructure
{
	class Graph
	{
	public:
		Graph(GameObject* _object, Graph* _parent = nullptr);
		~Graph() {};
		GameObject* object;
		Graph* parent;
		std::list<Graph> children;
	};
}