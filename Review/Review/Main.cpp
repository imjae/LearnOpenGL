#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Window.h"

int main()
{
	Window win = Window("ReviewOpenGL", 800, 600, 3, 3, GLFW_OPENGL_CORE_PROFILE);
	win.InitializeWindow();

	GLFWwindow* window = win.CreateWindow();
	if (window == NULL) 
		return -1;

	glfwMakeContextCurrent(window);

	return 0;
}