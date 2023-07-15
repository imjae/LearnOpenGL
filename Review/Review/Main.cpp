#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "MyWindow.h"

int main()
{
	MyWindow myWindow = MyWindow("ReviewOpenGL", 800, 600, 3, 3, GLFW_OPENGL_CORE_PROFILE);
	myWindow.InitializeWindow();

	GLFWwindow* window = myWindow.createWindow();
	if (window == NULL) return -1;

	glfwMakeContextCurrent(window);
	myWindow.setFramebufferSizeCallback(window);
	
	if (myWindow.LoadGlad() == -1) return -1;


	while(!glfwWindowShouldClose(window))
	{
		// �Է�
		myWindow.processInput(window);

		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ������


		// �̺�Ʈ Ȯ���ϰ� ���� ��ü
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}