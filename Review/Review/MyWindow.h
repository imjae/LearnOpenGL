#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class MyWindow
{
private:
	const char* title = "test";
	int width = 800;
	int height = 600;
	int majorVersion;
	int minorVersion;
	int openglProfile;

public:
	MyWindow();
	MyWindow(const char* title, int width, int height, int majorVersion, int minorVersion, int profile);
	
	void InitializeWindow();
	int InitializeGlad();

	void setFramebufferSizeCallback(GLFWwindow* window);

	GLFWwindow* createWindow();

	int getWidth();
	int getHeight();
};