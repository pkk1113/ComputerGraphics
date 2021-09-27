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

void AppBase::OnCursorPosX(double x)
{
	m_x = x;
	m_deltaX = m_x - m_prevX;
	m_prevX = m_x;
}

void AppBase::OnCursorPosY(double y)
{
	m_y = y;
	m_deltaY = m_y - m_prevY;
	m_prevY = m_y;
}

void AppBase::OnMouseWheel(double scroll)
{
	m_scroll = scroll;
}

void AppBase::OnMouseLeftButton(bool pressed)
{
	m_leftBtnPressed = pressed;
}

void AppBase::OnMouseRightButton(bool pressed)
{
	m_rightBtnPressed = pressed;
}

void AppBase::OnMouseMiddleButton(bool pressed)
{
	m_middleBtnPressed = pressed;
}

void AppBase::OnFramebufferSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void AppBase::Init()
{
}

void AppBase::Release()
{
}

void AppBase::Update(double deltaTime)
{
}                                        

void AppBase::Draw()
{
}
