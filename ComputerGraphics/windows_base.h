#pragma once

class AppBase;

namespace windows_base
{
	bool InitPlatformSettings(const char* title, int width, int height);
	bool ReleasePlatformSettings();
	bool RunApp(AppBase* app);

	bool GetKeyState(Key key);
	bool GetKeyDown(Key key);
	bool GetKeyUp(Key key);

	enum Key
	{
		LButton = VK_LBUTTON,
		RButton = VK_RBUTTON,
		MButton = VK_MBUTTON,
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z',
		Key_1 = '1',
		Key_2 = '2',
		Key_3 = '3',
		Key_4 = '4',
		Key_5 = '5',
		Key_6 = '6',
		Key_7 = '7',
		Key_8 = '8',
		Key_9 = '9',
		Key_0 = '0',
		Numpad_1 = VK_NUMPAD1,
		Numpad_2 = VK_NUMPAD2,
		Numpad_3 = VK_NUMPAD3,
		Numpad_4 = VK_NUMPAD4,
		Numpad_5 = VK_NUMPAD5,
		Numpad_6 = VK_NUMPAD6,
		Numpad_7 = VK_NUMPAD7,
		Numpad_8 = VK_NUMPAD8,
		Numpad_9 = VK_NUMPAD9,
		Numpad_0 = VK_NUMPAD0,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		Shift = VK_SHIFT,
		Alt = VK_MENU,
		Ctrl = VK_CONTROL,
		Tab = VK_TAB,
		Space = VK_SPACE,
		Enter = VK_RETURN,
		Esc = VK_ESCAPE,
		Left = VK_LEFT,
		Up = VK_UP,
		Down = VK_DOWN,
		Right = VK_RIGHT,
	};
}
