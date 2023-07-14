#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "MyWindow.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
}

int main()
{
	MyWindow myWindow = MyWindow("ReviewOpenGL", 800, 600, 3, 3, GLFW_OPENGL_CORE_PROFILE);
	myWindow.InitializeWindow();

	if (myWindow.InitializeGlad() == -1) return -1;

	GLFWwindow* window = myWindow.createWindow();
	if (window == NULL) return -1;

	glfwMakeContextCurrent(window);

	myWindow.setFramebufferSizeCallback(window);


	return 0;
}