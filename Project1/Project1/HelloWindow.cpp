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
	// GLFW 초기화
	glfwInit();
	// GLFW에게 OpenGL Context 버전 3.3을 사용하겠다는 것을 알리고, 
	// OpenGL Profile을 core로 사용하겠다고 설정
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW 윈도우 생성
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	// 생성한 윈도우를 주 컨텍스트로 설정
	glfwMakeContextCurrent(window);

	// GLAD를 사용해 OpenGL 함수 포인터 주소 로드
	// 이 동작이 있으여 OpenGL 함수들을 별다른 처리 없이 사용할 수 있음
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 윈도우 사이즈가 변결될 때, 호출되는 콜백 함수를 지정
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 버텍스 쉐이더 생성, 할당
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 버텍스 쉐이더 에러 체크
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 프래그먼트 쉐이더 생성, 할당
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 프래그먼트 에러 체크
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 쉐이더 프로그램 생성, 버텍스, 프래그먼트 쉐이더 링크
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// 쉐이더 프로그램 에러 체크
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// 링크된 버텍스, 프래그먼트 쉐이더 삭제
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 사각형에 맞는 버텍스 위치 설정
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // 우측 상단
		0.5f, -0.5f, 0.0f,  // 우측 하단
		-0.5f, -0.5f, 0.0f,  // 좌측 하단
		-0.5f,  0.5f, 0.0f   // 좌측 상단
	};

	// 위 버텍스 좌표의 인덱스로 삼각형을 구성하도록 데이터 셋팅
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// VAO, VBO, EBO 순서대로 버퍼 생성
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Vertext Array Object 바인딩
	glBindVertexArray(VAO);

	// Vertex Buffer Object 바인딩
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 이전에 바인딩된 버퍼(VBO)에 vertices 사이즈와 vertices 데이터 설정
	// GL_STATIC_DRAW는 유니티 오브젝트의 static 옵션 같음
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object 바인딩
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// 이전에 바인딩된 버퍼(EBO)에 indices 사이즈와 인덱스 데이터 설정
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 버텍스 쉐이더에서 설정된 입력 데이터의 location값 (여기서는 0)에 데이터를 어떤식으로 사용할 지 설정
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 렌더링 루프
	while (!glfwWindowShouldClose(window))
	{
		// 입력
		processInput(window);

		// 렌더링 명령
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// 이벤트 확인하고 버퍼 교체
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	// 윈도우, 콘텍스트 클리어
	glfwTerminate();
	return 0;
}