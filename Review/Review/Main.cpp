#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

#include "MyWindow.h"
#include "MyShader.h"

int main()
{
	MyWindow myWindow = MyWindow("ReviewOpenGL", 800, 600, 3, 3, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = myWindow.createWindow();
	if (window == NULL) return -1;

	MyShader shader = MyShader("vertexShader.shader", "fragmentShader.shader");

	float vertices[] =
	{
		-0.5f, 0.5f, 0.0f,		// 좌측 상단
		0.5f, 0.5f, 0.0f,		// 우측 상단
		-0.5f,-0.5f, 0.0f,		// 좌측 하단
		0.5f, -0.5f, 0.0f		// 우측 하단
	};

	int indices[] =
	{
		0, 1, 2,
		1, 2, 3
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(".\\images\\container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	while (!glfwWindowShouldClose(window))
	{
		// 입력
		myWindow.processInput(window);

		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 이벤트 확인하고 버퍼 교체
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteProgram(shader.ID);

	glfwTerminate();

	return 0;
}