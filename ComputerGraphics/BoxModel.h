#pragma once
#include "Model.h"

class BoxModel :
	public Model
{
	static std::vector<float> vertices;
	static std::vector<float> normals;
	static std::vector<float> uv;

public:
	BoxModel() : Model(vertices, normals, uv) {}
};

std::vector<float> BoxModel::vertices = {
	// up side
	+1.0f, +1.0f, +1.0f,
	+1.0f, +1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, +1.0f, +1.0f,

	// near side
	+1.0f, -1.0f, +1.0f,
	+1.0f, +1.0f,  +1.0f,
	-1.0f, +1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,
	-1.0f, -1.0f, +1.0f,

	// right side
	+1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, +1.0f, +1.0f,
	+1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,

	// down side
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, +1.0f,
	+1.0f, -1.0f, +1.0f,
	-1.0f, -1.0f, -1.0f,
	+1.0f, -1.0f, +1.0f,
	+1.0f, -1.0f, -1.0f,

	// far side
	-1.0f, -1.0f, -1.0f,
	-1.0f, +1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	+1.0f, +1.0f, -1.0f,
	+1.0f, -1.0f, -1.0f,

	// left side
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, +1.0f,
	-1.0f, +1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
};
std::vector<float> BoxModel::normals = {
	// up side
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	// near side
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	// right side
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	// down side
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,

	// far side
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	// left side
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
};
std::vector<float> BoxModel::uv = {
	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
};