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

	// 렌더링 루프
	while (!glfwWindowShouldClose(window))
	{
		// 입력
		processInput(window);

		// 렌더링 명령
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 이벤트 확인하고 버퍼 교체
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 윈도우, 콘텍스트 클리어
	glfwTerminate();
	return 0;
}