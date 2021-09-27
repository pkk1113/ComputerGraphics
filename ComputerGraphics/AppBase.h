#pragma once

class AppBase
{
private:
	double m_prevX;
	double m_prevY;

protected:
	int m_width;
	int m_height;
	
	// 마우스
	double m_x;
	double m_y;
	double m_deltaX;
	double m_deltaY;
	bool m_leftBtnPressed;
	bool m_middleBtnPressed;
	bool m_rightBtnPressed;
	double m_scroll;

	// 키보드
	enum class Key_
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		K1,
		K2,
		K3,
		K4,
		K5,
		K6,
		K7,
		K8,
		K9,
		K0,
		N1,
		N2,
		N3,
		N4,
		N5,
		N6,
		N7,
		N8,
		N9,
		N0,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		Esc,
		Tab,
		Shift,
		Ctrl,
		Alt,
		Space,
		Enter,
		Left,
		Right,
		Up,
		Bottom,
		COUNT, // 마지막에 둡니다.
	};
	int m_keyPressed[static_cast<int>(Key_::COUNT)];

public:
	AppBase(int _width, int _height);
	virtual ~AppBase();
	void OnCursorPosX(double x);
	void OnCursorPosY(double y);
	void OnMouseWheel(double scroll);
	void OnMouseLeftButton(bool pressed);
	void OnMouseRightButton(bool pressed);
	void OnMouseMiddleButton(bool pressed);
	void OnFramebufferSize(int width, int height);

public:
	virtual void Init();
	virtual void Release();
	virtual void Update(double deltaTime);
	virtual void Draw();
};

