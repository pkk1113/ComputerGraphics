#pragma once
#include "AppBase.h"
#include <glad/glad.h>

class DrawCubeApp : public AppBase
{
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_program = 0;
	GLfloat m_yaw = 0; // y축 회전
	GLfloat m_pitch = 0; // x축 회전

public:
	DrawCubeApp(int width, int height);

	virtual void Init() override;

	virtual void Release() override;

	virtual void Update(double deltaTime) override;

	virtual void Draw() override;
};

