#include "DevCamera.h"
#include "Input.h"
#include "AppState.h"

using namespace LowRenderer;
using namespace Core;

void DevCamera::Init( unsigned int width, unsigned int height)
{
	position = Vector3(0, 0, 5);
	forward = Vector3(0, 0, -1);
	Up = Vector3(0, 1, 0);
	rotation = Vector3();

	model = Matrix4::CreateTransformMatrix(position, rotation, Vector3(1, 1, 1));
	ViewMatrix = model.GetInverse();
	ProjectionMatrix = Matrix4::CreatePerspectiveMatrix(0.1, 5000, 90, width, height);
	VP = ProjectionMatrix * ViewMatrix;
	
}

void DevCamera::Update()
{

	if (IsMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		lastCursorX = Input::mousePos.x;
		lastCursorY = Input::mousePos.y;
		freeCamMode = !freeCamMode;
		if(freeCamMode)
			Input::HideCursor();
		else
			Input::ShowCursor();
	}

	if (freeCamMode)
	{
		UpdateCameraRotation();
		UpdateKeyboardInputs();
	}

	if (isMoving || isRotating)
	{
		model = Matrix4::CreateTransformMatrix(position, rotation, Vector3(1, 1, 1));
		ViewMatrix = model.GetInverse();
		VP = ProjectionMatrix * ViewMatrix;
		position = Vector3(model.matrix[0][3], model.matrix[1][3], model.matrix[2][3]);
		isMoving = false;
		isRotating = false;
	}
}

Vector3 LowRenderer::DevCamera::GetForwardVec()
{
	return forward;
}

void DevCamera::UpdateCameraRotation()
{
	if (Input::mousePos.x == lastCursorX && Input::mousePos.y == lastCursorY) return;
		
	float xoffset = Input::mousePos.x - lastCursorX;
	float yoffset = lastCursorY - Input::mousePos.y;
	lastCursorX = Input::mousePos.x;
	lastCursorY = Input::mousePos.y;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	rotation.y -= xoffset;
	rotation.x += yoffset;

	if (rotation.x > 89.0f)
		rotation.x = 89.0f;
	if (rotation.x < -89.0f)
		rotation.x = -89.0f;

	Vector3 direction;
	direction.x = -sin(rotation.y * DEG2RAD) * cos(rotation.x * DEG2RAD);
	direction.y = sin(rotation.x * DEG2RAD);
	direction.z = -cos(rotation.x * DEG2RAD) * cos(rotation.y * DEG2RAD);
	forward = direction.Normalize();

	isRotating = true;
}

void DevCamera::UpdateKeyboardInputs()
{
	float speed = moveSpeed * AppState::deltatime;

	if (glfwGetKey(Input::window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += forward * speed;
		isMoving = true;
	}

	if (glfwGetKey(Input::window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= forward * speed;
		isMoving = true;
	}

	if (glfwGetKey(Input::window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= forward.CrossProduct(Up).Normalize() * speed;
		isMoving = true;
	}

	if (glfwGetKey(Input::window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += forward.CrossProduct(Up).Normalize() * speed;
		isMoving = true;
	}

	if (glfwGetKey(Input::window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += Up * speed;
		isMoving = true;
	}

	if (glfwGetKey(Input::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		position -= Up * speed;
		isMoving = true;
	}
}

bool DevCamera::IsMouseButtonPressed(int button)
{
	if (glfwGetMouseButton(Input::window, button) == GLFW_PRESS)
	{
		if (!buttonHold)
		{
			buttonHold = true;
			return true;
		}
		return false;
	}

	buttonHold = false;
	return false;
}



 