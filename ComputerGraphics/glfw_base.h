#pragma once

class AppBase;

namespace glfw_base
{
	bool InitPlatformSettings(const char* title, int width, int height);
	bool ReleasePlatformSettings();
	bool RunApp(AppBase* app);
}
