#include "Window.h"

#include <iostream>

Window::Window(const char* title, int width, int height, int majorVersion, int minorVersion, int openglProfile)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->majorVersion = majorVersion;
	this->minorVersion = minorVersion;
	this->openglProfile = openglProfile;
}

void Window::InitializeWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}

GLFWwindow* Window::CreateWindow()
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	return window;
}