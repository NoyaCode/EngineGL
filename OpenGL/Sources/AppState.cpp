#include "AppState.h"
#include "Debug.h"
#include "Input.h"

using namespace Core;

void AppState::Update()
{
	UpdateDeltaTime();
	glfwGetWindowSize(Input::window, &windowWidth, &windowHeight);
}

void AppState::UpdateDeltaTime()
{
	currentFrame = glfwGetTime();
	deltatime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}