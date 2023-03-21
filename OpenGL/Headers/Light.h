#pragma once

#include "MyMaths.h"
#include "MonoBehaviour.h"
#include <vector>

using namespace Core::Maths;

namespace LowRenderer
{
	class Light : public MonoBehaviour
	{
	public:
		Light();
		Light(Vector3 color);
		Light(Vector3 _diffuseColor, Vector3 _ambientColor, Vector3 _specularColor);

	public:
		Vector3 diffuseColor;
		Vector3 ambientColor;
		Vector3 specularColor;
	};  

	class PointLight : public Light
	{
	public:
		using Light::Light;
		void Update() override;
		bool UpdateComponent(std::string* id) override;
		void Delete() override;
	};

	class DirectionalLight : public Light
	{
	public:
		using Light::Light;
		Vector3 direction;
		void Update() override;
		bool UpdateComponent(std::string* id) override;
		void Delete() override;
	};

	class SpotLight : public Light
	{
	public:
		using Light::Light;
		Vector3 direction;
		float angle;
		void Update() override;
		bool UpdateComponent(std::string* id) override;
		void Delete() override;
	};
}


