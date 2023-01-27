#pragma once
#include "Model.h"

class PlaneModel :
	public Model
{
	static std::vector<float> vertices;
	static std::vector<float> normals;
	static std::vector<float> uv;

public:
	PlaneModel() : Model(vertices, normals, uv) {}
};

std::vector<float> PlaneModel::vertices = {
	// up side
	+1.0f, 0.0f, +1.0f,
	+1.0f, 0.0f, -1.0f,
	-1.0f, 0.0f, -1.0f,
	+1.0f, 0.0f, +1.0f,
	-1.0f, 0.0f, -1.0f,
	-1.0f, 0.0f, +1.0f,
};
std::vector<float> PlaneModel::normals = {
	// up side
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};
std::vector<float> PlaneModel::uv = {
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
};