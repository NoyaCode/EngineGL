#include "Light.h"
#include "Renderer.h"

#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>

using namespace LowRenderer;


Light::Light()
{
	diffuseColor = Vector3(1, 1, 1);
	ambientColor = Vector3(1, 1, 1);
	specularColor = Vector3(1, 1, 1);
}


Light::Light(Vector3 color)
{
	diffuseColor = color;
	ambientColor = color;
	specularColor = color;
}

Light::Light(Vector3 _diffuseColor, Vector3 _ambientColor, Vector3 _specularColor)
{
	diffuseColor = _diffuseColor;
	ambientColor = _ambientColor;
	specularColor = _specularColor;
}

void LowRenderer::PointLight::Update()
{

}

bool LowRenderer::PointLight::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Point Light##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox(("active##" + *id).c_str(), &active);
		ImGui::Text("\nColor");
		ImGui::ColorEdit3(("Ambient##" + *id).c_str(), &ambientColor.x);
		ImGui::ColorEdit3(("Diffuse##" + *id).c_str(), &diffuseColor.x);
		ImGui::ColorEdit3(("Specular##" + *id).c_str(), &specularColor.x);
	}
	return popUp;
}

void LowRenderer::PointLight::Delete()
{
	std::vector<PointLight*>::iterator it = Renderer::currentPointLights.begin();
	for (PointLight* light : Renderer::currentPointLights)
	{
		if (light == this)
		{
			Renderer::currentPointLights.erase(it);
			return;
		}
		it++;
	}
}

void LowRenderer::DirectionalLight::Update()
{
	direction.x = -sin(gameObject->transform.rotation.y * DEG2RAD) * cos(gameObject->transform.rotation.x * DEG2RAD);
	direction.y = sin(gameObject->transform.rotation.x * DEG2RAD);
	direction.z = -cos(gameObject->transform.rotation.x * DEG2RAD) * cos(gameObject->transform.rotation.y * DEG2RAD);
}

bool LowRenderer::DirectionalLight::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Directional Light##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox("active##dir", &active);
		ImGui::Text("\nColor");
		ImGui::ColorEdit3(("Ambient##" + *id).c_str(), &ambientColor.x);
		ImGui::ColorEdit3(("Diffuse##" + *id).c_str(), &diffuseColor.x);
		ImGui::ColorEdit3(("Specular##" + *id).c_str(), &specularColor.x);
	}
	return popUp;
}

void LowRenderer::DirectionalLight::Delete()
{
	std::vector<DirectionalLight*>::iterator it = Renderer::currentDirectionalLights.begin();
	for (DirectionalLight* light : Renderer::currentDirectionalLights)
	{
		if (light == this)
		{
			Renderer::currentDirectionalLights.erase(it);
			return;
		}
		it++;
	}
}

void LowRenderer::SpotLight::Update()
{
	direction.x = -sin(gameObject->transform.rotation.y * DEG2RAD) * cos(gameObject->transform.rotation.x * DEG2RAD);
	direction.y = sin(gameObject->transform.rotation.x * DEG2RAD);
	direction.z = -cos(gameObject->transform.rotation.x * DEG2RAD) * cos(gameObject->transform.rotation.y * DEG2RAD);
}

bool LowRenderer::SpotLight::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Spot Light##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox(("active##" + *id).c_str(), &active);
		ImGui::Dummy(ImVec2(10, 10));
		ImGui::Text("\Angle");
		ImGui::DragFloat(("##angle" + *id).c_str(), &angle, 0.1, 0.1, 100);
		ImGui::Text("\nColor");
		ImGui::ColorEdit3(("Ambient##" + *id).c_str(), &ambientColor.x);
		ImGui::ColorEdit3(("Diffuse##" + *id).c_str(), &diffuseColor.x);
		ImGui::ColorEdit3(("Specular##" + *id).c_str(), &specularColor.x);
	}
	return popUp;
}

void LowRenderer::SpotLight::Delete()
{
	std::vector<SpotLight*>::iterator it = Renderer::currentSpotLights.begin();
	for (SpotLight* light : Renderer::currentSpotLights)
	{
		if (light == this)
		{
			Renderer::currentSpotLights.erase(it);
			return;
		}
		it++;
	}
}

