#pragma once
#include "AppBase.h"
#include <glad/glad.h>

class DrawTriangleApp : public AppBase
{
	GLuint _vao = 0;
	GLuint _vbo[2] = { 0, };
	GLuint _program = 0;

public:
	DrawTriangleApp(int width, int height);

	virtual void Init() override;

	virtual void Update(double _deltaTime) override;

	virtual void Draw() override;
};

