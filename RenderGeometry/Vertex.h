#pragma once
#include <GLM/glm/glm.hpp>
class Vertex
{
public:
	Vertex(glm::vec4);
	~Vertex();

	glm::vec4 position;
	glm::vec4 color;
};

