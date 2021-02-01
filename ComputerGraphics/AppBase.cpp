#include <iostream>
#include "AppBase.h"

AppBase::AppBase(int _width, int _height) :
	m_prevX(0.0),
	m_prevY(0.0),
	m_height(_height),
	m_width(_width),
	m_x(0.0),
	m_y(0.0),
	m_deltaX(0.0),
	m_deltaY(0.0),
	m_leftBtnPressed(false),
	m_middleBtnPressed(false),
	m_rightBtnPressed(false),
	m_scroll(0.0)
{
}

AppBase::~AppBase()
{
}

void AppBase::OnCursorPosX(double _x)
{
	m_x = _x;
	m_deltaX = m_x - m_prevX;
	m_prevX = m_x;
}

void AppBase::OnCursorPosY(double _y)
{
	m_y = _y;
	m_deltaY = m_y - m_prevY;
	m_prevY = m_y;
}

void AppBase::OnMouseWheel(double _scroll)
{
	m_scroll = _scroll;
}

void AppBase::OnMouseLeftButton(bool _pressed)
{
	m_leftBtnPressed = _pressed;
}

void AppBase::OnMouseRightButton(bool _pressed)
{
	m_rightBtnPressed = _pressed;
}

void AppBase::OnMouseMiddleButton(bool _pressed)
{
	m_middleBtnPressed = _pressed;
}

void AppBase::OnFramebufferSize(int _width, int _height)
{
	m_width = _width;
	m_height = _height;
}

void AppBase::Update(double _deltaTime)
{
}                                        

void AppBase::Draw()
{

}
