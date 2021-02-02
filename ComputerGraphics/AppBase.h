#pragma once

class AppBase
{
private:
	double m_prevX;
	double m_prevY;

protected:
	int m_width;
	int m_height;
	double m_x;
	double m_y;
	double m_deltaX;
	double m_deltaY;
	bool m_leftBtnPressed;
	bool m_middleBtnPressed;
	bool m_rightBtnPressed;
	double m_scroll;

public:
	AppBase(int _width, int _height);
	virtual ~AppBase();
	void OnCursorPosX(double _x);
	void OnCursorPosY(double _y);
	void OnMouseWheel(double _scroll);
	void OnMouseLeftButton(bool _pressed);
	void OnMouseRightButton(bool _pressed);
	void OnMouseMiddleButton(bool _pressed);
	void OnFramebufferSize(int _width, int _height);
public:
	virtual void Update(double _deltaTime);
	virtual void Draw();
};

