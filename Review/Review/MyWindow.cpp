#include "MyWindow.h"

#include <iostream>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

MyWindow::MyWindow()
{
	this->title = "DefaultTitle";
	this->width = 800;
	this->height = 600;
	this->majorVersion = 3;
	this->minorVersion = 3;
	this->openglProfile = GLFW_OPENGL_CORE_PROFILE;

	InitializeWindow();
}

MyWindow::MyWindow(const char* title, int width, int height, int majorVersion, int minorVersion, int openglProfile)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->majorVersion = majorVersion;
	this->minorVersion = minorVersion;
	this->openglProfile = openglProfile;

	InitializeWindow();
}

void MyWindow::InitializeWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}

int MyWindow::LoadGlad()
{
	int result = -1;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		result = -1;
	}
	else
	{
		result = 0;
	}

	return result;
}

void MyWindow::setFramebufferSizeCallback(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
}

void MyWindow::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

GLFWwindow* MyWindow::createWindow()
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	else
	{
		glfwMakeContextCurrent(window);
		setFramebufferSizeCallback(window);

		if (LoadGlad() == -1) return NULL;
	}

	return window;
}

int MyWindow::getWidth()
{
	return width;
}

int MyWindow::getHeight()
{
	return height;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}