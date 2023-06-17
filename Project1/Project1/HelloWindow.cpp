#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	// GLFW �ʱ�ȭ
	glfwInit();
	// GLFW���� OpenGL Context ���� 3.3�� ����ϰڴٴ� ���� �˸���, 
	// OpenGL Profile�� core�� ����ϰڴٰ� ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW ������ ����
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	// ������ �����츦 �� ���ؽ�Ʈ�� ����
	glfwMakeContextCurrent(window);

	// GLAD�� ����� OpenGL �Լ� ������ �ּ� �ε�
	// �� ������ ������ OpenGL �Լ����� ���ٸ� ó�� ���� ����� �� ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ������ ����� ����� ��, ȣ��Ǵ� �ݹ� �Լ��� ����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ������ ����
	while (!glfwWindowShouldClose(window))
	{
		// �Է�
		processInput(window);

		// ������ ���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// �̺�Ʈ Ȯ���ϰ� ���� ��ü
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// ������, ���ؽ�Ʈ Ŭ����
	glfwTerminate();
	return 0;
}