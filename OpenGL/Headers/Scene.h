#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include  <list>
#include "DevCamera.h"
#include "Mesh.h"
#include "GameObject.h"
#include "Light.h"
#include "ResourceManager.h"
#include "Graph.h"
#include "Collider.h"
#include "Collision.h"
#include "Camera.h"
#include "AppState.h"

#include "PlayerMovements.h"
#include "HeadRotation.h"
#include "Enemy.h"
#include "Rigidbody.h"

#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>

constexpr auto MAX_POINTLIGHTS = 3;

using namespace Core;
using namespace Resources;
using namespace LowRenderer;
using namespace Core::Maths;
using namespace DataStructure;
using namespace Physics;
using namespace Game;

namespace Resources
{
	enum class StateMenu
	{
		PLAY,
		MAINMENU,
		EDITOR,
		OPTION,
	};

	class Scene
	{
	public:
		Scene() {};
		~Scene() 
		{
			ResourceManager::DeleteMap();
		};

		void Init();
		void Update();

	public:
		Transform objectsTransform;

		DevCamera camera;

		Camera* gameCamera = nullptr;

		std::list<GameObject> gameObjects;
		std::list<Graph> sceneGraph;

	private:
		void LoadResources();
		void SwitchMode(AppState::Mode mode);

		// Updates

		void UpdateInspector();
		void UpdateHierarchy();
		void UpdateImGuiGraph(std::list<Graph>& nodeList);
		void UpdateGameObjects(std::list<Graph>& nodeList);

		// Add/Delete GameObjects

		void AddEmptyObject(std::string name, Graph* parent = nullptr, Transform transform = Transform());
		void AddModelObject(std::string modelName, std::string textureName = "cubeTexture", std::string shaderName = "mainShader", Graph* parent = nullptr, Transform transform = Transform());

		void AddPointLightObject(Vector3 position = Vector3(), Vector3 color = Vector3(1, 1, 1), Graph* parent = nullptr);
		void AddDirLightObject(Vector3 rotation = Vector3(), Vector3 color = Vector3(1, 1, 1), Graph* parent = nullptr);
		void AddSpotLightObject(Vector3 position = Vector3(), Vector3 rotation = Vector3(0, -1, 0), float angle = 12.0f, Vector3 color = Vector3(1, 1, 1), Graph* parent = nullptr);
		void DeleteGameObject(Graph& node);

		// Add Components 

		void AddMesh(GameObject* object, std::string modelName, std::string textureName = "cubeTexture", std::string shaderName = "mainShader");
		void AddPointLight(GameObject* object, Vector3 color = Vector3(1, 1, 1));
		void AddDirLight(GameObject* object, Vector3 color = Vector3(1, 1, 1));
		void AddSpotLight(GameObject* object, float angle = 12.0f, Vector3 color = Vector3(1, 1, 1));
		void AddCamera(GameObject* object);
		template <class T>
		void AddCollider(GameObject* object, Vector3 center = Vector3(), Vector3 size = Vector3(1, 1, 1), bool trigger = false);
		template <class T>
		void AddScript(GameObject* object);
		void AddRigidbody(GameObject* object);

		ImGuiTreeNodeFlags GetTreeFlags(Graph& node);

		void SetButtonInOptionImgui(std::string name, Input::Button moveChange);
		
	private:
		GameObject* selectedObject = nullptr;

		StateMenu stateMenu = StateMenu::MAINMENU;
		Input::Button buttonSelected = Input::Button::NULLBUTTON;

		unsigned int id = 0;
	};
}