#include "Input.h"

using namespace Core;

void Input::Update()
{
	glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
}

void Input::HideCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Input::ShowCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Input::GetButtonDown(Button inputButton)
{
	switch (inputButton)
	{
	case Button::FORWARD: return glfwGetKey(window, ForwardKey) == GLFW_PRESS; break;

	case Button::BACKWARD: return glfwGetKey(window, BackwardKey) == GLFW_PRESS; break;

	case Button::LEFT: return glfwGetKey(window, LeftKey) == GLFW_PRESS; break;

	case Button::RIGHT: return glfwGetKey(window, RightKey) == GLFW_PRESS; break;

	case Button::JUMP: return glfwGetKey(window, JumpKey) == GLFW_PRESS; break;

	default: return false;
	}
}

bool Input::IsEscapePressed()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if (!EscapeDown)
		{
			EscapeDown = true;
			return true;
		}
		return false;
	}
	EscapeDown = false;
	return false;
}

bool Core::Input::IsColliderKeyPressed()
{
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (!CKey)
		{
			CKey = true;
			return true;
		}
		return false;
	}
	CKey = false;
	return false;
}

void Input::ChangeControl(Button moveChange, int newKey)
{
	switch (moveChange)
	{
	case Core::Input::Button::FORWARD:
		ForwardKey = newKey;
		break;
	case Core::Input::Button::BACKWARD:
		BackwardKey = newKey;
		break;
	case Core::Input::Button::LEFT:
		LeftKey = newKey;
		break;
	case Core::Input::Button::RIGHT:
		RightKey = newKey;
		break;
	case Core::Input::Button::JUMP:
		JumpKey = newKey;
		break;
	default:
		break;
	}
}

char Input::GetKey(Button key)
{
	switch (key)
	{
	case Core::Input::Button::FORWARD:
		return ForwardKey;
	case Core::Input::Button::BACKWARD:		
		return BackwardKey;
	case Core::Input::Button::LEFT:
		return LeftKey;
	case Core::Input::Button::RIGHT:
		return RightKey;
	case Core::Input::Button::JUMP:
		return JumpKey;
	default:
		break;
	}
}

bool Input::CheckInput(int newKey)
{
	if (newKey == ForwardKey || newKey == BackwardKey || newKey == LeftKey || newKey == RightKey || newKey == JumpKey || newKey == GLFW_KEY_C)
	{
		return true;
	}
	return false;
}