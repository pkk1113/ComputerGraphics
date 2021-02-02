#include <iostream>
#include <chrono>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AppBase.h"
//////////////////////////////////////////////////////////////////////////
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 400;
//////////////////////////////////////////////////////////////////////////
AppBase* g_pApplication = nullptr;
//////////////////////////////////////////////////////////////////////////
void SetCursorPosCallback(GLFWwindow* window, double x, double y);
void SetMouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
void SetScrollCallback(GLFWwindow* window, double x, double y);
void SetFramebufferSizeCallback(GLFWwindow* window, int width, int height);
//////////////////////////////////////////////////////////////////////////
int main()
{
	glfwInit();
	glfwSetTime(0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 0);
	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwSetCursorPosCallback(window, SetCursorPosCallback);
	glfwSetMouseButtonCallback(window, SetMouseButtonCallback);
	glfwSetScrollCallback(window, SetScrollCallback);
	glfwSetFramebufferSizeCallback(window, SetFramebufferSizeCallback);

	// TODO:
	g_pApplication = new AppBase(WINDOW_WIDTH, WINDOW_HEIGHT);

	auto lastTime = std::chrono::system_clock::now();

	while (!glfwWindowShouldClose(window))
	{
		auto currentTime = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		g_pApplication->Update(deltaTime);
		g_pApplication->Draw();
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	delete g_pApplication;

	return 0;
}

void SetCursorPosCallback(GLFWwindow*, double _x, double _y)
{
	g_pApplication->OnCursorPosX(_x);
	g_pApplication->OnCursorPosY(_y);
}

void SetMouseButtonCallback(GLFWwindow*, int _button, int _action, int)
{
	switch (_button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:	g_pApplication->OnMouseLeftButton(_action == GLFW_PRESS);	break;
	case GLFW_MOUSE_BUTTON_RIGHT:	g_pApplication->OnMouseRightButton(_action == GLFW_PRESS);	break;
	case GLFW_MOUSE_BUTTON_MIDDLE:	g_pApplication->OnMouseMiddleButton(_action == GLFW_PRESS);	break;
	default: break;
	}
}

void SetScrollCallback(GLFWwindow*, double, double _y)
{

	g_pApplication->OnMouseWheel(_y);
}

void SetFramebufferSizeCallback(GLFWwindow*, int _width, int _height)
{
	std::cout << "framebuffer size(" << _width << ", " << _height << ")" << std::endl;
	g_pApplication->OnFramebufferSize(_width, _height);
}
