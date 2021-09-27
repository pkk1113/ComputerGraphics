#include "DrawCubeApp.h"

#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

DrawCubeApp::DrawCubeApp(int width, int height)
	: AppBase(width, height)
{
}

void DrawCubeApp::Init()
{
	// VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// VBO
	glGenBuffers(1, &m_vbo);

	// VBO_Position
	GLfloat vertexPositionData[] = {
		-1, -1, 1,
		1, -1, 1,
		-1, 1, 1,
		1, 1, 1
	};
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionData), vertexPositionData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Shader_vertex
	const GLchar* vertexShaderData = R"(
#version 450 core 
layout(location = 0) in vec3 i_pos;
layout(location = 0) uniform mat4 u_vpmat;
layout(location = 1) uniform mat4 u_mmat[6];
out vec3 vs_color;
void main()
{
	vec4 pos = u_mmat[gl_InstanceID] * vec4(i_pos.xyz, 1.0);
	gl_Position = u_vpmat * pos;
	
	vs_color = normalize(pos.xyz) * 0.5 + 0.5;
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
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Once
	glViewport(0, 0, m_width, m_height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	// Once_program
	glUseProgram(m_program);
}

void DrawCubeApp::Release()
{
	// 사용해제를 안 해도 지울 수 있지만
	// 습관적으로 하면 좋을 듯?
	//[선택] glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);

	// 사용 해제를 하고 지워야 합니다.
	glUseProgram(0);
	glDeleteProgram(m_program);
}

void DrawCubeApp::Update(double deltaTime)
{
	deltaTime *= 0.1f;

	m_yaw += deltaTime * glm::two_pi<float>();
	if (m_yaw > glm::two_pi<float>())
	{
		m_yaw = 0.f;
	}

	m_pitch += deltaTime * glm::two_pi<float>();
	if (m_pitch > glm::two_pi<float>())
	{
		m_pitch = 0.f;
	}
}


void DrawCubeApp::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection View Matrix
	auto aspect = (float)m_width / (float)m_height;
	auto pmat = glm::perspective(45.f, aspect, 0.01f, 20.f);

	const auto main_radius = 4.f;
	const auto radius = main_radius * -cos(m_pitch);
	const auto y = main_radius * sin(m_pitch);
	const auto x = radius * cos(m_yaw); 
	const auto z = radius * sin(m_yaw); 

	// projection view matrix
	auto vmat = glm::lookAt(glm::vec3(x, y, z), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	auto vpmat = pmat * vmat;
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(vpmat));

	// model matrix
	glm::mat4 mmat[] = {
		glm::rotate(0.f, glm::vec3(0, 1, 0)),
		glm::rotate(glm::half_pi<float>(), glm::vec3(0, 1, 0)),
		glm::rotate(glm::pi<float>(), glm::vec3(0, 1, 0)),
		glm::rotate(-glm::half_pi<float>(), glm::vec3(0, 1, 0)),
		glm::rotate(-glm::half_pi<float>(), glm::vec3(1, 0, 0)),
		glm::rotate(glm::half_pi<float>(), glm::vec3(1, 0, 0)),
	};
	glUniformMatrix4fv(1, 6, GL_FALSE, glm::value_ptr(mmat[0]));

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 6);
}
