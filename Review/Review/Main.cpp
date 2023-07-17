#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "MyWindow.h"
#include "MyShader.h"

int main()
{
	MyWindow myWindow = MyWindow("ReviewOpenGL", 800, 600, 3, 3, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = myWindow.createWindow();
	if (window == NULL) return -1;

	MyShader shader = MyShader("vertexShader.shader", "fragmentShader.shader");
	MyShader shader2 = MyShader("vertexShader.shader", "fragmentShader2.shader");

	float vertices1[] = {
		 -0.25f, 0.5f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
		  0.0f, -0.5f, 0.0f,
	};
	
	unsigned int VBO[2], VAO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float vertices2[] = {
		  0.0f, -0.5f, 0.0f,
		  0.25f, 0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
	};

	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window))
	{
		// �Է�
		myWindow.processInput(window);  

		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ������
		shader.use();
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		shader2.use();
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// �̺�Ʈ Ȯ���ϰ� ���� ��ü
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);

	glDeleteProgram(shader.ID);

	glfwTerminate();

	return 0;
}