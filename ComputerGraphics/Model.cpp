#include "Model.h"

Model::Model(std::vector<float> vertex, std::vector<float> normal, std::vector<float> uv)
{
	triangleCount = vertex.size() / 3;
	if (triangleCount == 0) return;

	// vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// vbo
	vertexBitFlag = 0;

	if (!vertex.empty()) {
		glGenBuffers(1, &m_vbos[Vertex_Flag]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[Vertex_Flag]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), (void*)vertex.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(Vertex_Flag);
		glVertexAttribPointer(Vertex_Flag, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		vertexBitFlag |= (1 << Vertex_Flag);
	}

	if (!normal.empty()) {
		glGenBuffers(1, &m_vbos[Normal_Flag]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[Normal_Flag]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normal.size(), (void*)normal.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(Normal_Flag);
		glVertexAttribPointer(Normal_Flag, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		vertexBitFlag |= (1 << Normal_Flag);
	}

	if (!uv.empty()) {
		glGenBuffers(1, &m_vbos[UV_Flag]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[UV_Flag]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv.size(), (void*)uv.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(UV_Flag);
		glVertexAttribPointer(UV_Flag, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		vertexBitFlag |= (1 << UV_Flag);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Model::~Model()
{
	glBindVertexArray(m_vao);

	if (vertexBitFlag && (1 << Vertex_Flag)) glDeleteBuffers(1, &m_vbos[Vertex_Flag]);
	if (vertexBitFlag && (1 << Normal_Flag)) glDeleteBuffers(1, &m_vbos[Normal_Flag]);
	if (vertexBitFlag && (1 << UV_Flag)) glDeleteBuffers(1, &m_vbos[UV_Flag]);

	glDeleteVertexArrays(1, &m_vao);
}

void Model::Render() {
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, triangleCount);
	glBindVertexArray(0);
}
