#include <GameApp.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <cstdio>

#ifdef DEBUG
#define DEBUG_MSG(fmt, ...) std::printf(fmt, __VA_ARGS__)
#else
#define DEBUG_MSG(fmt, ...)
#endif

inline GLFWwindow* g_Window = nullptr;

static void CleanUp() {
	glfwDestroyWindow(g_Window);
	glfwTerminate();
}

bool GameApp::Create(const std::string& title, uint32_t width, uint32_t height, GLVersionFlags versionFlag) {
	glfwInit();
	/**
	 * Selecting an opengl version to used based on the @{code versionFlag} 
	 */
	switch (versionFlag) {
	case GL_4_0:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		break;
	case GL_4_1:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		break;
	case GL_4_2:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		break;
	case GL_4_3:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		break;
	case GL_4_4:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		break;
	case GL_4_5:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		break;
	case GL_4_6:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		break;
	default:
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	/**
	 * Creating the window
	 */
	g_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (g_Window == nullptr) {
		DEBUG_MSG("failed to create window");
		return false;
	}
	/**
	 * Making the window's context the current one and then loading opengl function pointers.
	 */
	glfwMakeContextCurrent(g_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		DEBUG_MSG("failed to load OpenGL functions!");
		return false;
	}
	return true;
}

void GameApp::Run() {
	auto past = std::chrono::high_resolution_clock::now();
	OnCreate();
	while (!glfwWindowShouldClose(g_Window)) {
		auto now = std::chrono::high_resolution_clock::now();
		double dt = (now - past).count() / 1000000000.0;
		past = now;
		glfwPollEvents();
		OnUpdate(dt);
		glClear(GL_COLOR_BUFFER_BIT);
		OnRender();
		glfwSwapBuffers(g_Window);
	}
	OnExit();
	CleanUp();
}
