#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "DevCamera.h"
#include "Mesh.h"
#include "GameObject.h"
#include <vector>
#include "Light.h"
#include "MyMaths.h"
#include "Scene.h"
#include "Input.h"

using namespace LowRenderer;

namespace Core
{

	struct AppInit
	{
		unsigned int width;
		unsigned int height;
		unsigned int major;
		unsigned int minor;
		const char* title;
		void (*framebuffer_size_callback)(GLFWwindow* window, int width, int height);
		void (*glDebugOutput)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	};

	struct AppUpdate
	{
		void (*processInput)(GLFWwindow* window);
	};

	class App
	{

	public:
		GLFWwindow* window = nullptr;

	private:
		Scene scene;
	public:
		App();
		~App();
		void Init(Core::AppInit appInit);
		void Update(AppUpdate *appUpdate);
	};
}

