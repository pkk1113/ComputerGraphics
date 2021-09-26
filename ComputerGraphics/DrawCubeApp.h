#pragma once
#include "AppBase.h"
#include <glad/glad.h>

class DrawCubeApp : public AppBase
{
	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_program = 0;
	GLfloat m_gab = 0; // 면의 중심으로부터 면이 벌어진 정도
	GLfloat m_gabDir = 1.f; // 갭이 커졌다 작아졌다를 표현
	GLfloat m_yaw = 0; // y축 회전

public:
	DrawCubeApp(int width, int height);

	virtual void Init() override;

	virtual void Release() override;

	virtual void Update(double deltaTime) override;

	virtual void Draw() override;
};

