#pragma once
#include <string>
#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>

namespace Core 
{
	class GameObject;
}

namespace LowRenderer
{
	class MonoBehaviour
	{
	public:

		MonoBehaviour()
		{
			gameObject = nullptr;
		}
		~MonoBehaviour() {}

		bool IsActive(bool onlyGO = false);
		Core::GameObject* gameObject = nullptr;

		virtual void Update() = 0;
		void UpdateInspector(int index);
		virtual void Delete() = 0;
		bool active = true;

	protected:
		virtual bool UpdateComponent(std::string* id) = 0;
	};
}

