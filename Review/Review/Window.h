#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	const char* title = "test";
	int width = 800;
	int height = 600;
	int majorVersion;
	int minorVersion;
	int openglProfile;

public:
	Window(const char* title, int width, int height, int majorVersion, int minorVersion, int profile);
	
	void InitializeWindow();
	GLFWwindow* CreateWindow();
};