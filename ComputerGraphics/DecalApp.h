#pragma once
#include "AppBase.h"
#include <glad/glad.h>
#include <vector>

#include "Model.h"
#include "Shader.h"

class DecalApp : public AppBase
{
private:
	/*OpenGL Objects*/
	Model* m_groundModel = nullptr;
	Model* m_boxModel = nullptr;
	Shader* m_shader = nullptr;

	/*Fields*/
	float rotateY = 0;

public:
	DecalApp(int width, int height) : AppBase(width, height) {}
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(double deltaTime) override;
	virtual void Draw() override;

private:
	void InitModels();
	void InitShaders();
};

