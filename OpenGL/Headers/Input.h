#pragma once
#include "MyMaths.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Core
{
	static class Input
	{
		struct Double2
		{
			double x;
			double y;
		};

	public:
		enum class Button
		{
			NULLBUTTON,
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			JUMP,
		};

		inline static GLFWwindow* window;
		inline static Double2 mousePos;
		inline static bool showColliders = true;

	public:
		static void Update();
		static void HideCursor();
		static void ShowCursor();
		static bool GetButtonDown(Button inputButton);
		static bool IsEscapePressed();
		static bool IsColliderKeyPressed();
		static void ChangeControl(Button moveChange, int newKey);
		static char GetKey(Button key);
		static bool CheckInput(int newKey);

	private:
		
		inline static int ForwardKey = GLFW_KEY_W;
		inline static int BackwardKey = GLFW_KEY_S;
		inline static int LeftKey = GLFW_KEY_A;
		inline static int RightKey = GLFW_KEY_D;
		inline static int JumpKey = GLFW_KEY_SPACE;
		inline static int CKey = GLFW_KEY_C;
		inline static bool EscapeDown = false;
	};
}

