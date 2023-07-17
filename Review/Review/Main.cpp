#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "MyWindow.h"
#include "MyShader.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	MyWindow myWindow = MyWindow("ReviewOpenGL", 800, 600, 3, 3, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = myWindow.createWindow();
	if (window == NULL) return -1;

	MyShader shader = MyShader("vertexShader.shader", "fragmentShader.shader");

	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int indices[] = {  // 0부터 시작한다는 것을 명심하세요!
		0, 1, 3,   // 첫 번째 삼각형
		1, 2, 3    // 두 번째 삼각형
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

	while(!glfwWindowShouldClose(window))
	{
		// 입력
		myWindow.processInput(window);  

		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 렌더링
		shader.use();
		glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 이벤트 확인하고 버퍼 교체
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shader.ID);

	glfwTerminate();

	return 0;
}