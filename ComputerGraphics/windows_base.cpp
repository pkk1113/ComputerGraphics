/// header
#include "windows_base.h"
/// std
#include <iostream>
#include <chrono>
/// platform
#include <windowsx.h>
/// third_party
#include <glad/glad.h>
#include <gl/wglext.h>
/// project
#include "AppBase.h"

// windows_base 내 전역 변수/함수
//////////////////////////////////////////////////////////////////////////
AppBase* g_pApplication = nullptr;
HINSTANCE g_hinstance;
HWND g_hwnd = NULL;
HDC g_hdc = NULL;
HGLRC g_hrc = NULL;
TCHAR* g_title = NULL;
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

// header에서 성언한 함수의 구현
//////////////////////////////////////////////////////////////////////////
bool InitPlatformSettings(const TCHAR* title, int width, int height)
{
	// Regist window class
	g_hinstance = GetModuleHandle(nullptr);
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC;
	wcex.lpfnWndProc = &DefWindowProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = g_hinstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = 0;
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = title;
	wcex.hIconSm = nullptr;
	wcex.lpfnWndProc = WndProc;
	RegisterClassEx(&wcex);

	// Caculate window size for resolution.
	RECT rect = { 0, 0, width, height};
	int style = WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_BORDER |
		WS_CAPTION | WS_SYSMENU | WS_THICKFRAME;
	AdjustWindowRect(&rect, style, FALSE);

	// Create window
	g_hwnd = CreateWindow(title, title, style, CW_USEDEFAULT, CW_USEDEFAULT,
		rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, g_hinstance, nullptr);

	// Get device context
	g_hdc = GetDC(g_hwnd);

	// Create old version opengl context
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	int suggestedPixelFormat = ChoosePixelFormat(g_hdc, &pfd);
	SetPixelFormat(g_hdc, suggestedPixelFormat, &pfd);
	g_hrc = wglCreateContext(g_hdc);
	wglMakeCurrent(g_hdc, g_hrc);

	// Create extended opengl context
	auto wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	auto wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (wglChoosePixelFormatARB && wglCreateContextAttribsARB)
	{
		float fAttributes[] = { 0 };

		int iAttributes[] = {
			WGL_DRAW_TO_WINDOW_ARB,		GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB,		GL_TRUE,
			WGL_ACCELERATION_ARB,		WGL_FULL_ACCELERATION_ARB,
			WGL_DOUBLE_BUFFER_ARB,		GL_TRUE,
			WGL_COLOR_BITS_ARB,			32,
			WGL_DEPTH_BITS_ARB,			24,
			WGL_STENCIL_BITS_ARB,		8,
			WGL_SAMPLE_BUFFERS_ARB,		GL_TRUE,
			WGL_SAMPLES_ARB,			4,
			0
		};

		int attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
			WGL_CONTEXT_MINOR_VERSION_ARB, 5,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		UINT numPFD;
		BOOL valid = wglChoosePixelFormatARB(g_hdc, iAttributes, fAttributes, 1, &suggestedPixelFormat, &numPFD);

		if (valid != 0 && numPFD != 0)
		{
			SetPixelFormat(g_hdc, suggestedPixelFormat, &pfd);

			auto hrc2 = wglCreateContextAttribsARB(g_hdc, nullptr, attribs);

			if (hrc2)
			{
				wglMakeCurrent(/*hdc*/nullptr, /*hrc*/nullptr);
				wglDeleteContext(g_hrc);
				g_hrc = hrc2;
				wglMakeCurrent(g_hdc, g_hrc);
			}
		}
	}

	// Enable VSync
	auto wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if (wglSwapIntervalEXT) { wglSwapIntervalEXT(1); }

	// Enable extended GL functions
	gladLoadGL();

	return true;
}

bool ReleasePlatformSettings()
{
	if (g_hinstance == NULL)
	{
		return false;
	}

	wglDeleteContext(g_hrc);
	ReleaseDC(g_hwnd, g_hdc);
	DestroyWindow(g_hwnd);
	UnregisterClass(g_title, g_hinstance);

	return true;
}

bool RunApp(AppBase* app)
{
	// 앱 초기화
	g_pApplication = app;
	app->Init();

	// 화면 나오도록
	ShowWindow(g_hwnd, SW_NORMAL);

	MSG msg;
	auto lastTime = std::chrono::system_clock::now();

	while (true)
	{
		auto currentTime = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_pApplication->Update(deltaTime);
		g_pApplication->Draw();
		SwapBuffers(g_hdc);
	}

	return true;
}

// 함수 구현
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch (_msg)
	{
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_MOUSEMOVE:
	{
		double x = static_cast<double>(GET_X_LPARAM(_lparam));
		double y = static_cast<double>(GET_Y_LPARAM(_lparam));
		g_pApplication->OnCursorPosX(x);
		g_pApplication->OnCursorPosX(y);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		g_pApplication->OnMouseLeftButton(true);
		break;
	}
	case WM_LBUTTONUP:
	{
		g_pApplication->OnMouseLeftButton(false);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		g_pApplication->OnMouseRightButton(true);
		break;
	}
	case WM_RBUTTONUP:
	{
		g_pApplication->OnMouseRightButton(false);
		break;
	}
	case WM_MBUTTONDOWN:
	{
		g_pApplication->OnMouseMiddleButton(true);
		break;
	}
	case WM_MBUTTONUP:
	{
		g_pApplication->OnMouseMiddleButton(false);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		double scroll = static_cast<double>(GET_WHEEL_DELTA_WPARAM(_wparam));
		g_pApplication->OnMouseWheel(scroll);
		break;
	}
	case WM_SIZE:
	{
		int width = static_cast<int>(LOWORD(_lparam));
		int height = static_cast<int>(HIWORD(_lparam));
		g_pApplication->OnFramebufferSize(width, height);
		break;
	}
	default:
		break;
	}

	return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
}
