#include "Shader.h"

#ifdef _DEBUG
#include <iostream>
#endif

Shader::Shader(const char* vs, const char* fs)
{
	const GLchar* vertexShaderData = vs;
	const GLchar* fragmentShaderData = fs;
	GLint compileStatue;

	// Shader_vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderData, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatue);

#ifdef _DEBUG
	if (GL_FALSE == compileStatue)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		puts(errorLog);
	}
#endif

	// Shader_fragment
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderData, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatue);

#ifdef _DEBUG
	if (GL_FALSE == compileStatue)
	{
		GLchar errorLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		puts(errorLog);
	}
#endif

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::UnUse()
{
	glUseProgram(0);
}
