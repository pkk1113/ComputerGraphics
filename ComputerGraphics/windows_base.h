#pragma once
#include <windows.h>
class AppBase;

bool InitPlatformSettings(const char* title, int width, int height);
bool ReleasePlatformSettings();
bool RunApp(AppBase* app);