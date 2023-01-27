#pragma once
#include <glad/glad.h>

class Shader
{
private:
	GLuint m_program = 0;

public:
	Shader(
		const char* vertexShader,
		const char* fragmentShader);
	~Shader();

	void Use();
	void UnUse();
};