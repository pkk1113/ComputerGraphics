#pragma once

class AppBase;

namespace windows_base
{
	bool InitPlatformSettings(const char* title, int width, int height);
	bool ReleasePlatformSettings();
	bool RunApp(AppBase* app);
}
