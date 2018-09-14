#pragma once
#include "MyApplication.h"
#include <vector>
#include <GLM/glm/glm.hpp>

class MeshRenderer;
class Shader;

class RenderingGeometry : public MyApplication
{
public:
	RenderingGeometry();
	~RenderingGeometry();

	MeshRenderer* mesh;
	Shader* shader;

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	void Startup() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw() override;
};

