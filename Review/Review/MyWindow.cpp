#include "MyWindow.h"

#include <iostream>

MyWindow::MyWindow()
{

}

MyWindow::MyWindow(const char* title, int width, int height, int majorVersion, int minorVersion, int openglProfile)
{
	this->title = title;
	this->width = width;
	this->height = height;
	this->majorVersion = majorVersion;
	this->minorVersion = minorVersion;
	this->openglProfile = openglProfile;
}

void MyWindow::InitializeWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}

int MyWindow::InitializeGlad()
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

GLFWwindow* MyWindow::createWindow()
{
	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
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