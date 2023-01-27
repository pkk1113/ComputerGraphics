#pragma once
#include <glad/glad.h>
#include <vector>

class Model
{
public:
	enum VertexFlag : int {
		Vertex_Flag = 0, // xyz
		Normal_Flag = 1, // xyz
		UV_Flag = 2, // uv
		VBO_COUNT,
	};

private:
	int vertexBitFlag;
	GLuint m_vao;
	GLuint m_vbos[VBO_COUNT] = { 0, };
	int triangleCount;

public:
	Model(
		std::vector<float> vertex,
		std::vector<float> normal,
		std::vector<float> uv);
	virtual ~Model();

	void Render();
};