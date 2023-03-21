#pragma once
#include "Mesh.h"
#include "MyMaths.h"
#include "Graph.h"
#include <iostream>
#include  <list>

using namespace LowRenderer;
using namespace DataStructure;

namespace Core
{
	enum Layer
	{
		DEFAULT = 0,
		PLAYER,
		ENEMY,
	};

	class GameObject
	{
	public:
		std::string name;
		bool active = true;
		Layer layer = Layer::DEFAULT;
		std::vector<MonoBehaviour*> components;
		Transform transform;
		Matrix4 MVP;
		Graph* node;
		
	public:
		GameObject();
		GameObject(std::string name);
		~GameObject();
		void SetModel(Vector3 _position, Vector3 _rotation, Vector3 _scale);
		void SetModel(Transform _transform);
		Matrix4 GetModel();
		Matrix4 GetWorldModel();
		void UpdateMVP();
		
		template <class T>
		inline T* GetComponent(unsigned int index = 0)
		{
			T* res = nullptr;
			for (MonoBehaviour* component : components)
			{
				if (typeid(*component) == typeid(T))
				{
					res = (T*)component;
					if (index == 0)
						return res;
					else
						index--;
				}
			}
			return res;
		}

		template <class T>
		inline T* GetComponentInChildren(unsigned int index = 0)
		{
			T* res = nullptr;
			for (Graph child : node->children)
			{
				for (MonoBehaviour* component : child.object->components)
				{
					if (typeid(*component) == typeid(T))
					{
						res = (T*)component;
						if (index == 0)
							return res;
						else
							index--;
					}
				}
			}
			return res;
		}

		void Delete();
		void DeleteComponent(MonoBehaviour* component);

	private:
		Matrix4 localModel;
		Matrix4 worldModel;
	};
}
