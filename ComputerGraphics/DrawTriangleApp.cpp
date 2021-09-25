#include "DrawTriangleApp.h"

#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

DrawTriangleApp::DrawTriangleApp(int width, int height)
	: AppBase(width, height)
{
}

void DrawTriangleApp::Init()
{
	// VAO
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// VBO
	glGenBuffers(2, _vbo);

	// VBO_Position
	GLfloat vertexPositionData[] = {
		-0.5f, -0.5f, 0.f,
		0.5f, -0.5f, 0.f,
		0.f, 0.45f, 0.f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionData), vertexPositionData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// VBO_Color
	GLfloat vertexColorData[] = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f,
	};
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColorData), vertexColorData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	// Shader_vertex
	const GLchar* vertexShaderData = R"(
#version 450 core 
layout(location = 0) in vec3 i_pos;
layout(location = 1) in vec3 i_color;
layout(location = 0) uniform mat4 u_mvpMat;
out vec3 vs_color;
void main()
{
	vs_color = i_color;
	gl_Position = u_mvpMat * vec4(i_pos, 1.0);
}
)";
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderData, nullptr);
	glCompileShader(vertexShader);

	GLint compileStatue;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatue);
	if (GL_FALSE == compileStatue)
	{
#ifdef _DEBUG
		GLchar errorLog[512];
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		puts(errorLog);
#endif
	}

	// Shader_fragment
	const GLchar* fragmentShaderData = R"(
#version 450 core 
in vec3 vs_color;
layout(location = 0) out vec4 fragment_color;

void main()
{
	fragment_color = vec4(vs_color, 1.0);
}
)";
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderData, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatue);
	if (GL_FALSE == compileStatue)
	{
#ifdef _DEBUG
		GLchar errorLog[512];
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		puts(errorLog);
#endif
	}

	// Program
	_program = glCreateProgram();
	glAttachShader(_program, vertexShader);
	glAttachShader(_program, fragmentShader);
	glLinkProgram(_program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Once
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.7f, 0.8f, 0.9f, 1.f);
	
	// Once_program
	glUseProgram(_program);
	auto aspect = (float)m_width / (float)m_height;
	auto vmat = glm::lookAt(glm::vec3(0, 0, -2.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	auto pmat = glm::perspective(45.f, aspect, 0.01f, 20.f);
	auto vpmat = pmat * vmat;
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(vpmat));
}

void DrawTriangleApp::Update(double _deltaTime)
{
}

void DrawTriangleApp::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
}
