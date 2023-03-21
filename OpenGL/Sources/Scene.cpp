#include "Scene.h"
#include "Renderer.h"
#include "Input.h"
#include <vector>

#include <imgui_internal.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_opengl3_loader.h>



//-------------------------------------------------------------------------------------------------------------------------------------
//                                        MAIN FUNCTIONS
//-------------------------------------------------------------------------------------------------------------------------------------

void Resources::Scene::Init()
{
	camera.Init(AppState::windowWidth, AppState::windowHeight);

	LoadResources();

	// PLAYER

	AddEmptyObject("Player", nullptr, Transform(Vector3(), Vector3(0, 90, 0)));
	Graph* playerNode = gameObjects.back().node;
	AddRigidbody(playerNode->object);
	gameObjects.back().layer = Layer::PLAYER;

	AddCollider<SphereCollider>(playerNode->object, Vector3(), Vector3(0.52, NULL, NULL));
	AddCollider<BoxCollider>(playerNode->object, Vector3(0, -0.5, 0), Vector3(0.4, 0.15, 0.4), true);
	AddScript<PlayerMovements>(playerNode->object);

	AddEmptyObject("Head", playerNode, Transform());
	AddScript<HeadRotation>(&gameObjects.back());

	AddEmptyObject("Camera", gameObjects.back().node, Transform(Transform(Vector3(0, 1, -2.5), Vector3(-15, 180, 0), Vector3(1, 1, 1))));
	AddCamera(&gameObjects.back());

	AddModelObject("boo", "booTexture", "mainShader", playerNode, Transform(Vector3(0, -0.52, -0.055), Vector3(), Vector3(0.012, 0.012, 0.012)));

	AddEmptyObject("Lights");
	AddSpotLightObject(Vector3(82, 2, 0), Vector3(-90, 0, 0), 40, Vector3(1, 1, 1), &sceneGraph.back());
	AddDirLightObject(Vector3(45, 45, 0), Vector3(1, 1, 1), &sceneGraph.back());
	AddEmptyObject("Point Lights", &sceneGraph.back());
	AddPointLightObject(Vector3(-1, 0, 2), Vector3(0, 0, 1), &sceneGraph.back().children.back());
	AddPointLightObject(Vector3(0, 0, 2), Vector3(1, 1, 1), &sceneGraph.back().children.back());
	AddPointLightObject(Vector3(1, 0, 2), Vector3(1, 0, 0), &sceneGraph.back().children.back());

	AddEmptyObject("World");

	AddModelObject("skybox", "skyboxTexture", "noLightsShader", &sceneGraph.back(), Transform(Vector3(0, -100, 0), Vector3(0, 0, 0), Vector3(1, 1, 1)));

	AddModelObject("myCube", "cubeTexture", "mainShader");
	DeleteGameObject(sceneGraph.back());

	// PLATFORMS

	AddEmptyObject("Platforms", &sceneGraph.back());
	Graph* platformsNode = gameObjects.back().node;
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(0, -3, 0), Vector3(), Vector3(10, 2, 10)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(12, -3, 0), Vector3(), Vector3(5, 2, 5)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(17, -1, 0), Vector3(), Vector3(5, 2, 5)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(24, -1, 0), Vector3(30, 0, 0), Vector3(5, 2, 5)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(31, -1, 0), Vector3(-30, 0, 0), Vector3(5, 2, 5)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("mySphere", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(38, -1, 0), Vector3(), Vector3(2, 2, 2)));
	AddCollider<SphereCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(48, -1, 0), Vector3(0, 0, 30), Vector3(12, 2, 2)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("burger", "burgerTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(60, -5, 0), Vector3(0, 0, 0), Vector3(0.8, 0.8, 0.8)));
	AddCollider<BoxCollider>(&gameObjects.back(), Vector3(0, 2, 0), Vector3(4, 5, 4));
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(68, -3, 0), Vector3(), Vector3(5, 2, 5)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", platformsNode, Transform(Vector3(80, -3, 0), Vector3(), Vector3(10, 2, 10)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("chest","chestTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(83, -2, 0), Vector3(0, -70, 0), Vector3(0.8, 0.8, 0.8)));
	AddEmptyObject("collider", gameObjects.back().node, Transform(Vector3(), Vector3(0, -20, 0)));
	AddCollider<BoxCollider>(&gameObjects.back(), Vector3(0.1, 1.25, 0.1), Vector3(3, 2.5, 2.5));
	AddModelObject("goomba", "goombaTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(4, -2, 0), Vector3(0, -90, 0), Vector3(0.03, 0.03, 0.03)));
	gameObjects.back().layer = Layer::ENEMY;
	AddCollider<BoxCollider>(&gameObjects.back(), Vector3(0, 40, 0), Vector3(50, 80, 50));
	AddScript<Enemy>(&gameObjects.back());
	Enemy* enemy = (Enemy*)gameObjects.back().components.back();
	enemy->AddPathPoint(Vector3(4, -2, -2));
	enemy->AddPathPoint(Vector3(4, -2, 2));

	AddModelObject("goomba", "goombaTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(15.25, 0, 1.75), Vector3(0, -90, 0), Vector3(0.03, 0.03, 0.03)));
	gameObjects.back().layer = Layer::ENEMY;
	AddCollider<BoxCollider>(&gameObjects.back(), Vector3(0, 40, 0), Vector3(50, 80, 50));
	AddScript<Enemy>(&gameObjects.back());
	enemy = (Enemy*)gameObjects.back().components.back();
	enemy->AddPathPoint(Vector3(15.25, 0, -1.75));
	enemy->AddPathPoint(Vector3(18.75, 0, -1.75));
	enemy->AddPathPoint(Vector3(18.75, 0, 1.75));
	enemy->AddPathPoint(Vector3(15.25, 0, 1.75));

	AddModelObject("goomba", "goombaTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(75.75, -2, 0), Vector3(0, -90, 0), Vector3(0.03, 0.03, 0.03)));
	gameObjects.back().layer = Layer::ENEMY;
	AddCollider<BoxCollider>(&gameObjects.back(), Vector3(0, 40, 0), Vector3(50, 80, 50));
	AddScript<Enemy>(&gameObjects.back());
	enemy = (Enemy*)gameObjects.back().components.back();
	enemy->AddPathPoint(Vector3(75.75, -2, 2));
	enemy->AddPathPoint(Vector3(75.75, -2, -2));
	

	/* AddModelObject("ball","ballTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(-5, -1.2, 4), Vector3(0, 0, 0), Vector3(0.05, 0.05, 0.05)));*/
	AddModelObject("myCapsule", "cubeTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(-3.5, 0, 3), Vector3(0, 0, 0), Vector3(0.5, 0.5, 0.5)));
	AddCollider<CapsuleCollider>(&gameObjects.back());
	AddModelObject("myCapsule", "cubeTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(3.5, 0.5, 3), Vector3(90, 0, 0), Vector3(0.5, 0.5, 0.5)));
	AddCollider<CapsuleCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(-3.5, -1, -3.5), Vector3(45, 45, 45), Vector3(1, 1, 1)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(81, -1, 5.5), Vector3(0, 0, 0), Vector3(10, 2.5, 1)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(81, -1, -5.5), Vector3(0, 0, 0), Vector3(10, 2.5, 1)));
	AddCollider<BoxCollider>(&gameObjects.back());
	AddModelObject("cube", "cubeTexture", "mainShader", &sceneGraph.back(), Transform(Vector3(85.5, -1, 0), Vector3(0, 0, 0), Vector3(1, 2.5, 10)));
	AddCollider<BoxCollider>(&gameObjects.back());

	

	if (AppState::sceneMode == AppState::Mode::EDITOR)
	{
		Renderer::currentVP = &camera.VP;
	}
	else
	{
		glfwSetCursorPos(Input::window, AppState::windowWidth / 2.0f, AppState::windowHeight / 2.0f);
		Renderer::currentVP = &gameCamera->VP;
		Input::HideCursor();
	}
}

void Resources::Scene::Update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (AppState::sceneMode == AppState::Mode::EDITOR) // EDITOR MODE
	{
		camera.Update();
		Renderer::currentViewPos = &camera.position;
		UpdateHierarchy();
		UpdateInspector();
		UpdateGameObjects(sceneGraph);
		Collision::UpdateCollisions();
		Renderer::RenderColliders();

		ImGui::Begin("PlayMode", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
		ImGui::SetWindowPos(ImVec2(AppState::windowWidth / 2.0f - 47.5, -20));
		ImGui::SetWindowSize(ImVec2(95, 60));
		ImGui::Indent();
		ImGui::Dummy(ImVec2(2, 2));
		if (ImGui::Button("PLAY"))
		{
			stateMenu = StateMenu::MAINMENU;
			SwitchMode(AppState::Mode::PLAY);
		}
		ImGui::Unindent();
		ImGui::End();

		if (Input::IsEscapePressed())
			glfwSetWindowShouldClose(Input::window, true);
	}
	else                                               // PLAY MODE
	{
		switch (stateMenu) 
		{
		case Resources::StateMenu::PLAY:
		{
			Input::HideCursor();
			Matrix4 camModel = gameCamera->gameObject->GetWorldModel();
			Vector3 pos = Vector3(camModel.matrix[0][3], camModel.matrix[1][3], camModel.matrix[2][3]);
			Renderer::currentViewPos = &pos;
			UpdateGameObjects(sceneGraph);
			Collision::UpdateCollisions();
			if (Input::showColliders)
				Renderer::RenderColliders();

			if (Input::IsEscapePressed())
			{
				stateMenu = StateMenu::MAINMENU;
			}
			if (Input::IsColliderKeyPressed())
				Input::showColliders = !Input::showColliders;
			
			break;
		}
		case Resources::StateMenu::MAINMENU:
		{
			Input::ShowCursor();
			AppState::sceneMode = AppState::Mode::PLAY;
			ImGui::Begin("Menu", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::SetWindowPos(ImVec2(0, -20));
			ImGui::SetWindowSize((ImVec2(AppState::windowWidth, AppState::windowHeight + 20)));
			ImGui::Text("\n\n\n\n\n\n\n\n");
			ImGui::Indent((AppState::windowWidth / 2) - 45);
			ImGui::Text("Platformer");
			ImGui::Unindent((AppState::windowWidth / 2) - 45);
			ImGui::Indent(AppState::windowWidth / 3);

			ImGui::Text("\n\n\n\n");
			if (ImGui::Button("Start", ImVec2(AppState::windowWidth / 3, 50)))
			{
				stateMenu = StateMenu::PLAY;
			}
			ImGui::Text("\n\n");
			if (ImGui::Button("Editor", ImVec2(AppState::windowWidth / 3, 50)))
			{
				stateMenu = StateMenu::EDITOR;
				SwitchMode(AppState::Mode::EDITOR);
			}
			ImGui::Text("\n\n");
			if (ImGui::Button("Options", ImVec2(AppState::windowWidth / 3, 50)))
			{
				stateMenu = StateMenu::OPTION;
				if (buttonSelected != Input::Button::NULLBUTTON)
					buttonSelected = Input::Button::NULLBUTTON;
			}
			ImGui::Text("\n\n");
			if (ImGui::Button("Quit", ImVec2(AppState::windowWidth / 3, 50)))
			{
				glfwSetWindowShouldClose(Input::window, true);
			}
			if (Input::IsEscapePressed())
			{
				glfwSetWindowShouldClose(Input::window, true);
			}
			ImGui::Unindent(AppState::windowWidth / 3);

			ImGui::End();
			break;
		}
		case Resources::StateMenu::OPTION:
		{
			ImGui::Begin("Options", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::SetWindowPos(ImVec2(0, -20));
			ImGui::SetWindowSize((ImVec2(AppState::windowWidth, AppState::windowHeight + 20)));

			ImGui::Indent(AppState::windowWidth / 2);
			ImGui::Dummy(ImVec2(0, 110));
			ImGui::Text("Options");
			ImGui::Unindent(AppState::windowWidth / 2);

			ImGui::Dummy(ImVec2(0, 60));
			SetButtonInOptionImgui("Forward", Input::Button::FORWARD);
			ImGui::Dummy(ImVec2(0, 40));
			SetButtonInOptionImgui("Backward", Input::Button::BACKWARD);
			ImGui::Dummy(ImVec2(0, 40));
			SetButtonInOptionImgui("Right", Input::Button::RIGHT);
			ImGui::Dummy(ImVec2(0, 40));
			SetButtonInOptionImgui("Left", Input::Button::LEFT);
			ImGui::Dummy(ImVec2(0, 40));
			SetButtonInOptionImgui("Jump", Input::Button::JUMP);


			if (Input::IsEscapePressed())
			{
				if (buttonSelected != Input::Button::NULLBUTTON)
					buttonSelected = Input::Button::NULLBUTTON;
				stateMenu = StateMenu::MAINMENU;
			}
			ImGui::End();
			break;
		}
		case Resources::StateMenu::EDITOR:
		{
			SwitchMode(AppState::Mode::EDITOR);
			AppState::sceneMode = AppState::Mode::EDITOR;
		}
		default:
			break;
		}
	}
}

void Resources::Scene::LoadResources()
{
	Shader* mainShader = ResourceManager::Create<Shader>("mainShader", "Resources/Shaders/");
	mainShader->SetShaders("Resources/Shaders/MainVertexShader.vert", "Resources/Shaders/MainFragmentShader.frag");
	Shader* noLightsShader = ResourceManager::Create<Shader>("noLightsShader", "Resources/Shaders/");
	noLightsShader->SetShaders("Resources/Shaders/NoLights.vert", "Resources/Shaders/NoLights.frag");
	Shader* ColliderShader = ResourceManager::Create<Shader>("colliderShader", "Resources/Shaders/");
	ColliderShader->SetShaders("Resources/Shaders/Collider.vert", "Resources/Shaders/Collider.frag");

	std::string name = "chest";
	ResourceManager::Create<Model>(name, "Resources/Obj/Chest.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/Chest.png");

	name = "burger";
	ResourceManager::Create<Model>(name, "Resources/Obj/hamburger.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/hamburger.png");

	name = "boo";
	ResourceManager::Create<Model>(name, "Resources/Obj/boo.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/boo.png");

	name = "skybox";
	ResourceManager::Create<Model>(name, "Resources/Obj/skybox.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/skybox1.png");

	name = "cube";
	ResourceManager::Create<Model>(name, "Resources/Obj/cube.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/brick.png");

	name = "ball";
	ResourceManager::Create<Model>(name, "Resources/Obj/ball.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/ball.PNG");

	name = "goomba";
	ResourceManager::Create<Model>(name, "Resources/Obj/goomba.obj");
	ResourceManager::Create<Texture>(name + "Texture", "Resources/Textures/goomba.PNG");

	name = "myCube";
	ResourceManager::CustomCreate(name, Core::Maths::CreateCube(1));

	name = "mySphere";
	ResourceManager::CustomCreate(name, Core::Maths::CreateSphere(1));

	name = "myCapsule";
	ResourceManager::CustomCreate(name, Core::Maths::CreateCapsule(1, 2, 5, 10));

}

void Resources::Scene::SwitchMode(AppState::Mode mode)
{
	AppState::sceneMode = mode;

	switch (mode)
	{
	case AppState::Mode::EDITOR:
		Renderer::currentVP = &camera.VP;
		break;

	case AppState::Mode::PLAY:
		glfwSetCursorPos(Input::window, AppState::windowWidth / 2.0f, AppState::windowHeight / 2.0f);
		Renderer::currentVP = &gameCamera->VP;
		break;

	default: break;
	}
}

//--------------------------------------------------------------------------------------------------------------------
//				UPDATES
//--------------------------------------------------------------------------------------------------------------------

void Resources::Scene::UpdateInspector()
{
	ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);

	ImGui::SetWindowPos(ImVec2(AppState::windowWidth - ImGui::GetWindowSize().x, 0));
	ImGui::SetWindowSize(ImVec2(ImGui::GetWindowSize().x, AppState::windowHeight));

	if (selectedObject)
	{
		ImGui::Indent();
		ImGui::Checkbox("##active", &selectedObject->active);
		ImGui::Unindent();
		ImGui::SameLine();

		std::string key = strrchr((selectedObject->name).c_str(), '#');
		std::string name = selectedObject->name.substr(0, selectedObject->name.size() - key.size() - 1);
		char inputBuffer[128];
#pragma warning(suppress : 4996)
		std::strcpy(inputBuffer, name.c_str());
		if (ImGui::InputText("##Name", inputBuffer, 128))
		{
			selectedObject->name = inputBuffer;
			selectedObject->name += '#' + key;
		}

		ImGui::Dummy(ImVec2(5, 5));
		ImGui::Separator();
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::DragFloat3("Position", &selectedObject->transform.position.x, 0.25, -100, 100);
			ImGui::DragFloat3("Rotation", &selectedObject->transform.rotation.x, 0.25, -360, 360);
			ImGui::DragFloat3("Scale", &selectedObject->transform.scale.x, 0.01, 0.01, 100);
		}
		unsigned int index = 0;
		for (MonoBehaviour* c : selectedObject->components)
		{
			ImGui::NewLine();
			c->UpdateInspector(index);
			index++;
		}
		ImGui::NewLine();

		if (ImGui::BeginPopupContextItem("AddComponent"))
		{
			if (ImGui::BeginMenu("Mesh"))
			{
				if (ImGui::MenuItem("Cube"))
					AddMesh(selectedObject, "cube");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Light"))
			{
				if (ImGui::MenuItem("Directional"))
					AddDirLight(selectedObject);

				if (ImGui::MenuItem("Point"))
					AddPointLight(selectedObject);

				if (ImGui::MenuItem("Spot"))
					AddSpotLight(selectedObject);

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Collider"))
			{
				if (ImGui::MenuItem("Box"))
					AddCollider<BoxCollider>(selectedObject);

				if (ImGui::MenuItem("Sphere"))
					AddCollider<SphereCollider>(selectedObject);

				if (ImGui::MenuItem("Capsule"))
					AddCollider<CapsuleCollider>(selectedObject);


				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}
		if (ImGui::Button("Add Component"))
		{
			ImGui::OpenPopup("AddComponent");
		}
	}
	ImGui::End();
}

void Resources::Scene::UpdateHierarchy()
{
	ImGui::Begin("Scene Hierarchy", 0, ImGuiWindowFlags_NoMove);
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(ImGui::GetWindowSize().x, AppState::windowHeight));

	if (ImGui::BeginPopupContextItem("NewGameObject"))
	{
		if (ImGui::Selectable("Empty GameObject"))
		{
			AddEmptyObject("GameObject");
		}
		if (ImGui::Selectable("Cube"))
		{
			AddModelObject("cube", "cubeTexture", "mainShader");
			AddCollider<BoxCollider>(&gameObjects.back());
		}
		if (ImGui::Selectable("Sphere"))
		{
			AddModelObject("mySphere", "cubeTexture", "mainShader");
			AddCollider<SphereCollider>(&gameObjects.back());
		}
		ImGui::EndPopup();
	}

	UpdateImGuiGraph(sceneGraph);

	ImGui::NewLine();
	if (ImGui::Button("Add GameObject"))
	{
		ImGui::OpenPopup("NewGameObject");
	}
	ImGui::End();
}

void Resources::Scene::UpdateImGuiGraph(std::list<Graph>& nodeList)
{
	for (Graph& node : nodeList)
	{
		if (!node.object->active)
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.5, 0.5, 0.5, 1));

		bool opened = ImGui::TreeNodeEx(node.object->name.c_str(), GetTreeFlags(node));
		if (ImGui::BeginPopupContextItem("NewChild"))
		{
			if (ImGui::Selectable("Empty GameObject"))
			{
				AddEmptyObject("GameObject", &node);
			}
			if (ImGui::Selectable("Cube"))
			{
				AddModelObject("cube", "cubeTexture", "mainShader", &node);
			}
			if (ImGui::Selectable("Delete"))
			{
				DeleteGameObject(node);
				ImGui::EndPopup();
				ImGui::TreePop();
				return;
			}
			ImGui::EndPopup();
		}
		if (ImGui::IsItemClicked(1))
		{
			ImGui::OpenPopup("NewChild");
		}
		if (ImGui::IsItemClicked())
		{
			selectedObject = node.object;
		}
		if (opened)
		{
			if (node.children.size() > 0)
			{
				UpdateImGuiGraph(node.children);
			}
			ImGui::TreePop();
		}

		if (!node.object->active)
			ImGui::PopStyleColor();
	}
}


void Resources::Scene::UpdateGameObjects(std::list<Graph>& nodeList)
{

	for (Graph& node : nodeList)
	{
		if (!node.object->active)
			continue;

		node.object->UpdateMVP();

		for (MonoBehaviour* c : node.object->components)
		{
			c->Update();
		}

		if (node.children.size() > 0)
		{
			UpdateGameObjects(node.children);
		}

	}

	nodeList.front().object->UpdateMVP();
}


//--------------------------------------------------------------------------------------------------------------------
//				ADD/DELETE GAMEOBJECTS
//--------------------------------------------------------------------------------------------------------------------

void Resources::Scene::AddEmptyObject(std::string name, Graph* parent, Transform transform)
{
	std::string number = std::to_string(id);
	GameObject newObject(name + "##" + number); id++;

	gameObjects.push_back(newObject);

	if (parent)
	{
		Graph node(&gameObjects.back(), parent);
		parent->children.push_back(node);
		gameObjects.back().node = &parent->children.back();
	}

	else
	{
		Graph node(&gameObjects.back());
		sceneGraph.push_back(node);
		gameObjects.back().node = &sceneGraph.back();
	}

	gameObjects.back().SetModel(transform);
}

void Resources::Scene::AddModelObject(std::string modelName, std::string textureName, std::string shaderName, Graph* parent, Transform transform)
{
	std::string number = std::to_string(id);
	AddEmptyObject(modelName, parent, transform);
	AddMesh(&gameObjects.back(), modelName, textureName, shaderName);
}

void Resources::Scene::AddPointLightObject(Vector3 position, Vector3 color, Graph* parent)
{
	if (Renderer::currentPointLights.size() >= MAX_POINT_LIGHTS)
	{
		DEBUG_LOG("Max lights number (%i) reached. New light not added.", MAX_POINT_LIGHTS);
		return;
	}

	AddEmptyObject("PointLight", parent, Transform(position, Vector3(), Vector3(1, 1, 1)));
	AddPointLight(&gameObjects.back(), color);
}

void Resources::Scene::AddDirLightObject(Vector3 rotation, Vector3 color, Graph* parent)
{
	if (Renderer::currentDirectionalLights.size() >= MAX_DIR_LIGHTS)
	{
		DEBUG_LOG("Max directional lights number (1) reached. New light not added.");
		return;
	}

	AddEmptyObject("DirectionalLight", parent, Transform(Vector3(), rotation, Vector3(1, 1, 1)));
	AddDirLight(&gameObjects.back(), color);
}

void Resources::Scene::AddSpotLightObject(Vector3 position, Vector3 rotation, float angle, Vector3 color, Graph* parent)
{
	if (Renderer::currentSpotLights.size() >= MAX_SPOT_LIGHTS)
	{
		DEBUG_LOG("Max spot lights number (1) reached. New light not added.");
		return;
	}

	AddEmptyObject("SpotLight", parent, Transform(position, rotation, Vector3(1, 1, 1)));
	AddSpotLight(&gameObjects.back(), angle, color);
}

void Resources::Scene::DeleteGameObject(Graph& node)
{
	node.object->Delete();
	if (node.parent)
	{
		std::list<Graph>::iterator position = node.parent->children.begin();
		for (Graph& children : node.parent->children)
		{
			if (&children == &node)
			{
				node.parent->children.erase(position);
				break;
			}
			position++;
		}
	}
	else
	{
		std::list<Graph>::iterator position = sceneGraph.begin();
		for (Graph& children : sceneGraph)
		{
			if (&children == &node)
			{
				sceneGraph.erase(position);
				break;
			}
			position++;
		}
	}

	std::list<GameObject>::iterator position = gameObjects.begin();
	for (GameObject& children : gameObjects)
	{
		if (&children == node.object)
		{
			gameObjects.erase(position);
			break;
		}
		position++;
	}
}

//--------------------------------------------------------------------------------------------------------------------
//				ADD COMPONENTS
//--------------------------------------------------------------------------------------------------------------------

void Resources::Scene::AddMesh(GameObject* object, std::string modelName, std::string textureName, std::string shaderName)
{
	Mesh* mesh = new Mesh;
	mesh->data = ResourceManager::Get<Model>(modelName);
	mesh->shader = ResourceManager::Get<Shader>(shaderName);
	mesh->texture = ResourceManager::Get<Texture>(textureName);
	mesh->data->SetBuffersAndVAO();
	MonoBehaviour* component = (MonoBehaviour*)mesh;

	component->gameObject = object;
	object->components.push_back(component);
}

void Resources::Scene::AddPointLight(GameObject* object, Vector3 color)
{
	if (Renderer::currentPointLights.size() >= MAX_POINT_LIGHTS)
	{
		DEBUG_LOG("Max lights number (%i) reached. New light not added.", MAX_POINT_LIGHTS);
		return;
	}

	PointLight* light = new PointLight(color);
	light->gameObject = object;
	MonoBehaviour* component = (MonoBehaviour*)light;

	object->components.push_back(component);
	Renderer::currentPointLights.push_back((PointLight*)component);
}

void Resources::Scene::AddDirLight(GameObject* object, Vector3 color)
{
	if (Renderer::currentDirectionalLights.size() >= MAX_DIR_LIGHTS)
	{
		DEBUG_LOG("Max lights number (%i) reached. New light not added.", MAX_DIR_LIGHTS);
		return;
	}

	DirectionalLight* light = new DirectionalLight(color);
	light->gameObject = object;
	MonoBehaviour* component = (MonoBehaviour*)light;

	object->components.push_back(component);
	Renderer::currentDirectionalLights.push_back((DirectionalLight*)component);
}

void Resources::Scene::AddSpotLight(GameObject* object, float angle, Vector3 color)
{
	if (Renderer::currentSpotLights.size() >= MAX_SPOT_LIGHTS)
	{
		DEBUG_LOG("Max lights number (%i) reached. New light not added.", MAX_SPOT_LIGHTS);
		return;
	}

	SpotLight* light = new SpotLight(color);
	light->gameObject = object;
	light->angle = angle;
	MonoBehaviour* component = (MonoBehaviour*)light;

	object->components.push_back(component);
	Renderer::currentSpotLights.push_back((SpotLight*)component);
}

void Resources::Scene::AddCamera(GameObject* object)
{
	if (gameCamera != nullptr)
	{
		DEBUG_LOG("Max lights number 1 reached. New Camera not added.");
		return;
	}

	Camera* newCamera = new Camera();
	newCamera->gameObject = object;
	newCamera->Init(AppState::windowWidth, AppState::windowHeight);
	MonoBehaviour* component = (MonoBehaviour*)newCamera;

	object->components.push_back(component);
	gameCamera = (Camera*)component;
}

template <class T>
void Resources::Scene::AddCollider(GameObject* object, Vector3 center, Vector3 size, bool trigger)
{
	if (typeid(T) == typeid(BoxCollider))
	{
		T* collider = new T();
		BoxCollider* box = (BoxCollider*)collider;
		box->gameObject = object;
		box->Init();
		box->center = center;
		box->size = size;
		box->isTrigger = trigger;
		MonoBehaviour* component = (MonoBehaviour*)box;
		object->components.push_back(component);
		Collision::currentColliders.push_back((Collider*)component);
	}
	else if (typeid(T) == typeid(SphereCollider))
	{
		T* collider = new T();
		SphereCollider* sphere = (SphereCollider*)collider;
		sphere->gameObject = object;
		sphere->Init();
		sphere->center = center;
		sphere->radius = size.x;
		sphere->isTrigger = trigger;
		MonoBehaviour* component = (MonoBehaviour*)sphere;
		object->components.push_back(component);
		Collision::currentColliders.push_back((Collider*)component);
	}
	else if (typeid(T) == typeid(CapsuleCollider))
	{
		T* collider = new T();
		CapsuleCollider* capsule = (CapsuleCollider*)collider;
		capsule->gameObject = object;
		capsule->Init();
		capsule->center = center;
		capsule->radius = size.x;
		capsule->height = size.y;
		capsule->isTrigger = trigger;
		MonoBehaviour* component = (MonoBehaviour*)capsule;
		object->components.push_back(component);
		Collision::currentColliders.push_back((Collider*)component);
	}
}

template<class T>
void Resources::Scene::AddScript(GameObject* object)
{
	bool IsInherit = std::is_base_of<Script, T>::value;
	Assert(!IsInherit);

	T* script = new T();
	Script* newScript = (Script*)script;
	newScript->gameObject = object;
	newScript->Init();
	MonoBehaviour* component = (MonoBehaviour*)newScript;

	object->components.push_back(component);
}

void Resources::Scene::AddRigidbody(GameObject* object)
{
	Rigidbody* rb = new Rigidbody();
	rb->gameObject = object;
	rb->Init();
	MonoBehaviour* component = (MonoBehaviour*)rb;

	object->components.push_back(component);
}

ImGuiTreeNodeFlags Resources::Scene::GetTreeFlags(Graph& node)
{
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen;
	if (node.children.size() <= 0)
		treeNodeFlags += ImGuiTreeNodeFlags_Leaf;
	if (selectedObject == node.object)
		treeNodeFlags += ImGuiTreeNodeFlags_Selected;

	return treeNodeFlags;
}

void Resources::Scene::SetButtonInOptionImgui(std::string name, Input::Button moveChange)
{
	uint32_t f = Input::GetKey(moveChange);
	std::string control;
	switch (f)
	{
	case 32:
		control = "SPACE";
		break;
	default:
		control = (char)f;
		break;
	}
	ImGui::Indent(AppState::windowWidth * 2 / 5);
	ImGui::Text(name.c_str());
	ImGui::SameLine(200);
	ImGui::Unindent(AppState::windowWidth * 2 / 5);
	ImGui::Indent(AppState::windowWidth / 2);

	if (ImGui::Button(control.c_str(), ImVec2(AppState::windowHeight / 4, 50.0f)))
	{
		buttonSelected = moveChange;
	}
	if (moveChange == buttonSelected)
	{
		ImGui::SameLine(AppState::windowWidth * 4 / 6);
		ImGui::Text("button selected");
	}
	ImGui::Unindent(AppState::windowWidth / 2);

	if (buttonSelected != Input::Button::NULLBUTTON)
	{
		for (int i = 0; i < GLFW_KEY_LAST; i++)
		{
			if (glfwGetKey(Input::window, i) == GLFW_PRESS)
			{
				if (i == GLFW_KEY_ESCAPE)
				{
					continue;
				}
				if (Input::CheckInput(i))
				{
					if (moveChange == buttonSelected)
					{
						ImGui::SameLine(AppState::windowWidth * 4 / 5);
						ImGui::Text("Already used !!");
						break;
					}
				}
				else
				{
					Input::ChangeControl(buttonSelected, i);
					buttonSelected = Input::Button::NULLBUTTON;
					break;
				}
			}
		}
	}
}
