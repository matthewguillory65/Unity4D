#pragma once
#include <iostream>
#include "MyApplication.h"
#include "Transform.h"
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
	Transform* transform = new Transform();

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::mat4 movement;

	void Startup() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw() override;

	std::vector<glm::vec4> genHalfCircle(int np, int radius);
	std::vector<unsigned int> getIndices(int np, int nm);
	std::vector<glm::vec4> rotateHalfCirlce(std::vector<glm::vec4> points, unsigned int rotate);
	std::vector<unsigned int> getCubeIndices();
	std::vector<glm::vec4> genCube();
};

