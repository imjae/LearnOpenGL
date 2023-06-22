#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
"}\0";

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor=ourColor;\n"
"}\0";

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

	// ���ؽ� ���̴� ����, �Ҵ�
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// ���ؽ� ���̴� ���� üũ
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// �����׸�Ʈ ���̴� ����, �Ҵ�
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// �����׸�Ʈ ���� üũ
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ���̴� ���α׷� ����, ���ؽ�, �����׸�Ʈ ���̴� ��ũ
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// ���̴� ���α׷� ���� üũ
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ��ũ�� ���ؽ�, �����׸�Ʈ ���̴� ����
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// �簢���� �´� ���ؽ� ��ġ ����
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // ���� ���
		0.5f, -0.5f, 0.0f,  // ���� �ϴ�
		-0.5f, -0.5f, 0.0f,  // ���� �ϴ�
		-0.5f,  0.5f, 0.0f   // ���� ���
	};

	// �� ���ؽ� ��ǥ�� �ε����� �ﰢ���� �����ϵ��� ������ ����
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// VAO, VBO, EBO ������� ���� ����
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Vertext Array Object ���ε�
	glBindVertexArray(VAO);

	// Vertex Buffer Object ���ε�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ������ ���ε��� ����(VBO)�� vertices ������� vertices ������ ����
	// GL_STATIC_DRAW�� ����Ƽ ������Ʈ�� static �ɼ� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object ���ε�
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// ������ ���ε��� ����(EBO)�� indices ������� �ε��� ������ ����
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ���ؽ� ���̴����� ������ �Է� �������� location�� (���⼭�� 0)�� �����͸� ������� ����� �� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ������ ����
	while (!glfwWindowShouldClose(window))
	{
		// �Է�
		processInput(window);

		// ������ ���
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// �̺�Ʈ Ȯ���ϰ� ���� ��ü
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// ������, ���ؽ�Ʈ Ŭ����
	glfwTerminate();
	return 0;
}