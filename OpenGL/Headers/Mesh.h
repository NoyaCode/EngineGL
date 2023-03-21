#pragma once
#include "MyMaths.h"
#include "IResource.h"
#include "MonoBehaviour.h"

using namespace Core::Maths;
using namespace Resources;

namespace LowRenderer
{
	class Mesh : public MonoBehaviour
	{
	public:
		Mesh();
		~Mesh() {};
		void Update() override;
		bool UpdateComponent(std::string* id) override;
		void Delete() override {};
		Model* data = nullptr;
		Shader* shader = nullptr;
		Texture* texture = nullptr;
	};
}