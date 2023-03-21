#pragma once
#include "MyMaths.h"
#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace Core::Maths;

namespace LowRenderer
{
	class DevCamera
	{
	public:
		Matrix4 VP;
		Matrix4 model;
		Vector3 position;

	public:

		DevCamera(){};
		~DevCamera() {};
		void Init(unsigned int width, unsigned int height);
		void Update();
		Vector3 GetForwardVec();

	private:
		Matrix4 ViewMatrix;
		Matrix4 ProjectionMatrix;

		Vector3 rotation;
		Vector3 forward;
		Vector3 Up;
		
		float moveSpeed = 5;
		float rotationSpeed = 10;
		
		double lastCursorX = NULL;
		double lastCursorY = NULL;
		
		bool isMoving = false;
		bool isRotating = false;
		bool freeCamMode = false;
		bool buttonHold = false;
		

	private:
		void UpdateKeyboardInputs();
		void UpdateCameraRotation();
		bool IsMouseButtonPressed(int button);
	};
}
