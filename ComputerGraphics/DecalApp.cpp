#include "DecalApp.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "BoxModel.h"
#include "PlaneModel.h"

void DecalApp::Init()
{
	InitModels();
	InitShaders();

	glViewport(0, 0, m_width, m_height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
}

void DecalApp::Release()
{
	delete m_groundModel;
}

void DecalApp::Update(double deltaTime)
{
	rotateY += deltaTime * 180.0f;
	if (rotateY >= 360) {
		rotateY -= 360;
	}
}

void DecalApp::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->Use();

	/*
	* 카메라는 (4, 4, 4) 위치에서 (0, 0, 0) 위치를 봅니다.
	*/
	auto aspect = (float)m_width / (float)m_height;
	auto pmat = glm::perspective(45.f, aspect, 0.01f, 20.f);
	auto vmat = glm::lookAt(glm::vec3(4, 4, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	auto vpmat = pmat * vmat;
	glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(vpmat));

	/*
	* 바닥은 3x3 크기로 (0, 0, 0)에 둡니다.
	*/
	{
		auto mmat =
			glm::translate(glm::vec3(0, 0, 0)) *
			glm::rotate(glm::radians(0.0f), glm::vec3(0, 1, 0)) *
			glm::scale(glm::vec3(3, 1, 3)) *
			glm::identity<glm::mat4x4>();
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(mmat));
		m_groundModel->Render();
	}

	/*
	* 상자는 1x1 크기로 (0, 1, 0)에 둡니다. 2초에 한바퀴를 돕니다.
	*/
	{
		auto mmat =
			glm::translate(glm::vec3(0, 1.0f, 0)) *
			glm::rotate(glm::radians(rotateY), glm::vec3(0, 1, 0)) *
			glm::scale(glm::vec3(1, 1, 1)) *
			glm::identity<glm::mat4x4>();
		glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(mmat));
		m_boxModel->Render();
	}
}

void DecalApp::InitModels()
{
	m_groundModel = new PlaneModel();

	m_boxModel = new BoxModel();
}

void DecalApp::InitShaders()
{
	// Shader_vertex
	const GLchar* vs = R"(
#version 450 core 

layout(location = 0) in vec3 i_vertex;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec3 i_uv;

layout(location = 0) uniform mat4 u_vpmat;
layout(location = 1) uniform mat4 u_mmat;

out vec3 vs_color;

void main()
{
	vec4 pos = u_vpmat * u_mmat * vec4(i_vertex.xyz, 1.0);
	gl_Position =  pos;
	
	vs_color = i_normal.xyz * 0.5 + 0.5;
}
)";

	// Shader_fragment
	const GLchar* fs = R"(
#version 450 core
 
in vec3 vs_color;

layout(location = 0) out vec4 fragment_color;

void main()
{
	fragment_color = vec4(vs_color, 1.0);
}
)";

	m_shader = new Shader(vs, fs);
}
