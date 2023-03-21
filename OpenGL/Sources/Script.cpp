#include "Script.h"
#include "Input.h"
#include "AppState.h"

void Game::Script::Update()
{
	if (AppState::sceneMode == AppState::Mode::PLAY && IsActive())
		UpdateScript();
}
