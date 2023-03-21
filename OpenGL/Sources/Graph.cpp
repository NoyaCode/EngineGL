#include "Graph.h"
#include "GameObject.h"

DataStructure::Graph::Graph(GameObject* _object, Graph* _parent)
{
	object = _object;
	object->node = this;
	parent = _parent;
}
