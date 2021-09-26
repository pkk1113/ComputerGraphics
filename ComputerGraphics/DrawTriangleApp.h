#pragma once
#include "AppBase.h"
#include <glad/glad.h>

class DrawTriangleApp : public AppBase
{
	GLuint m_vao = 0;
	GLuint m_vbo[2] = { 0, };
	GLuint m_program = 0;

public:
	DrawTriangleApp(int width, int height);

	virtual void Init() override;

	virtual void Release() override;

	virtual void Update(double deltaTime) override;

	virtual void Draw() override;
};

