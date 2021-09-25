//> �÷��� ����(�ϳ��� Ȱ��ȭ)
//---------------------------
//#define USE_WINDOWS_BASE 1
#define USE_GLFW_BASE 1
//---------------------------
#ifdef USE_WINDOWS_BASE
#include "windows_base.h"
using namespace windows_base;
#elif USE_GLFW_BASE
#include "glfw_base.h"
using namespace glfw_base;
#endif

//> â ���� ����
#define WINDOW_TITLE "Draw Triagnle"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

//> �� ����
#include "DrawTriangleApp.h"

int main()
{
	InitPlatformSettings(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);

	// TODO:
	auto app = new DrawTriangleApp(WINDOW_WIDTH, WINDOW_HEIGHT);

	RunApp(app);
	ReleasePlatformSettings();
}
