#pragma once
#include <GLFW/glfw3.h>

namespace Core
{
	static class AppState
	{
	public:
		enum class Mode
		{
			EDITOR,
			PLAY,
		};

		inline static Mode sceneMode = Mode::PLAY;

	public:
		static void Update();
		inline static double deltatime;
		inline static const float fixedDeltatime = 0.002f;
		inline static int windowWidth;
		inline static int windowHeight;

	private:
		inline static double currentFrame = glfwGetTime();
		inline static double lastFrame = currentFrame;
		static void UpdateDeltaTime();
	};
}