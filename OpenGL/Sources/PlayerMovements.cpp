#include "PlayerMovements.h"
#include "AppState.h"


using namespace Game;
using namespace Core;

void Game::PlayerMovements::Init()
{
	rb = gameObject->GetComponent<Rigidbody>();
	groundCheck = gameObject->GetComponent<BoxCollider>();
}

void PlayerMovements::UpdateScript()
{
	UpdateRotation();
	UpdateMovements();

	if (groundCheck->collide) // Check if grounded
		grounded = true;
	else
		grounded = false;

	if (gameObject->transform.position.y < -20) // Respawn
	{
		ResetPos();
	}		
}

bool PlayerMovements::UpdateComponent(std::string* id)
{
	bool opened = ImGui::CollapsingHeader(("Script : PlayerMovements##" + *id).c_str(), ImGuiTreeNodeFlags_DefaultOpen);

	bool popUp = false;
	if (ImGui::IsItemClicked(1))
	{
		popUp = true;
	}

	if (opened)
	{
		ImGui::Checkbox(("active##" + *id).c_str(), &active);
		ImGui::Dummy(ImVec2(10, 10));
		ImGui::Checkbox(("Is Grounded##" + *id).c_str(), &grounded);
		ImGui::Dummy(ImVec2(10, 10));
		ImGui::DragFloat(("MoveSpeed##" + *id).c_str(), &moveSpeed, 1, 0, 1000);
	}

	return popUp;
}

void Game::PlayerMovements::ResetPos()
{
	glfwSetCursorPos(Input::window, AppState::windowWidth / 2.0f, AppState::windowHeight / 2.0f);
	gameObject->transform = Transform(Vector3(), Vector3(0, 90, 0));
	rb->velocity = Vector3();
}

void PlayerMovements::UpdateRotation()
{
	if (Input::mousePos.x == lastCursorX) return;
	else if (lastCursorX == NULL) { lastCursorX = Input::mousePos.x; return; }

	float xoffset = Input::mousePos.x - lastCursorX;
	lastCursorX = Input::mousePos.x;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;

	gameObject->transform.rotation.y -= xoffset;

	Vector3 direction;
	direction.x = -sin(gameObject->transform.rotation.y * DEG2RAD) * cos(gameObject->transform.rotation.x * DEG2RAD);
	direction.z = -cos(gameObject->transform.rotation.x * DEG2RAD) * cos(gameObject->transform.rotation.y * DEG2RAD);
	forward = direction.Normalize();
}

void PlayerMovements::UpdateMovements()
{
	if (rb == nullptr)
		return;

	Vector3 direction;

	if (Input::GetButtonDown(Input::Button::FORWARD))
		direction -= forward;

	if (Input::GetButtonDown(Input::Button::BACKWARD))
		direction += forward;

	if (Input::GetButtonDown(Input::Button::LEFT))
		direction += forward.CrossProduct(Up).Normalize();

	if (Input::GetButtonDown(Input::Button::RIGHT))
		direction -= forward.CrossProduct(Up).Normalize();

	float speed = moveSpeed;
	if (grounded)
	{
		speed *= 2;
	}
	direction = direction.Normalize() * speed * AppState::deltatime;
	direction.y = rb->velocity.y;

	if (Input::GetButtonDown(Input::Button::JUMP) && grounded)
		direction.y = jumpForce;

	
	rb->velocity = direction;
}

