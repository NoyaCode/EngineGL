#include "GameObject.h"
#include "Renderer.h"

using namespace Core;


GameObject::GameObject()
{
	name = "GameObject";
}

GameObject::GameObject(std::string _name)
{
	name = _name;
}

GameObject::~GameObject()
{
	for (MonoBehaviour* c : components)
	{
		delete c;
	}
}

void GameObject::SetModel(Vector3 _position, Vector3 _rotation, Vector3 _scale)
{
	transform.position = _position;
	transform.rotation = _rotation;
	transform.scale = _scale;

	localModel = Matrix4::CreateTransformMatrix(_position, _rotation, _scale);
	if (node->parent != nullptr)
		worldModel = node->parent->object->GetWorldModel() * localModel;

	else
		worldModel = localModel;
}

void GameObject::SetModel(Transform _transform)
{
	transform.position = _transform.position;
	transform.rotation = _transform.rotation;
	transform.scale = _transform.scale;

	localModel = Matrix4::CreateTransformMatrix(transform.position, transform.rotation, transform.scale);
	if (node->parent != nullptr)
		worldModel = node->parent->object->GetWorldModel() * localModel;

	else
		worldModel = localModel;
}

Matrix4 GameObject::GetModel()
{
	return localModel;
}

Matrix4 GameObject::GetWorldModel()
{
	return worldModel;
}

void GameObject::UpdateMVP()
{
	localModel = Matrix4::CreateTransformMatrix(transform.position, transform.rotation, transform.scale);

	if (node->parent != nullptr)
	{
		worldModel = node->parent->object->GetWorldModel() * localModel;
		MVP = *Renderer::currentVP * worldModel;
	}
	else
	{
		worldModel = localModel;
		MVP = *Renderer::currentVP * worldModel;
	}
}

void Core::GameObject::Delete()
{
	for (MonoBehaviour* c : components)
	{
		c->Delete();
	}

	for (Graph& c : node->children)
	{
		c.object->Delete();
	}
}

void Core::GameObject::DeleteComponent(MonoBehaviour* component)
{
	std::vector<MonoBehaviour*>::iterator it = components.begin();
	for (MonoBehaviour* c : components)
	{
		if (c == component)
		{
			components.erase(it);
			delete(c);
			return;
		}
		it++;
	}
}



