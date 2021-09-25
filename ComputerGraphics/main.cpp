#include "glfw_base.h"
#include "AppBase.h"
//////////////////////////////////////////////////////////////////////////

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 400;
constexpr char WINDOW_TITLE[] = u8"GLFW ���ؿ�!";

//////////////////////////////////////////////////////////////////////////
int main()
{
	InitPlatformSettings(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// TODO:
	AppBase* app = new AppBase(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	RunApp(app);
	ReleasePlatformSettings();
}
