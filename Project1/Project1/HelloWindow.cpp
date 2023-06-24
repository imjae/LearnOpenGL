#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor=vec4(ourColor, 1.0);\n"
"}\n";

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
		// ��ġ              // �÷�
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ���� �ϴ�
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ���� �ϴ�
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // �� 
	};

	// VAO, VBO, EBO ������� ���� ����
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Vertext Array Object ���ε�
	glBindVertexArray(VAO);

	// Vertex Buffer Object ���ε�
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// ������ ���ε��� ����(VBO)�� vertices ������� vertices ������ ����
	// GL_STATIC_DRAW�� ����Ƽ ������Ʈ�� static �ɼ� ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���ؽ� ���̴����� ������ �Է� �������� location�� (���⼭�� 0)�� �����͸� ������� ����� �� ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

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

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// �̺�Ʈ Ȯ���ϰ� ���� ��ü
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shaderProgram);

	// ������, ���ؽ�Ʈ Ŭ����
	glfwTerminate();
	return 0;
}