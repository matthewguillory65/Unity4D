#pragma once
#include "MyApplication.h"
#include <vector>
#include <GLM/glm/glm.hpp>
#include "Shader.h"


class MeshRenderer
{
public:
	MeshRenderer();
	~MeshRenderer();

	struct Vertex
	{
		glm::vec4 m_position;
		glm::vec4 m_color;
		glm::vec4 normal;
		glm::vec3 UV;
	};

	void initialize(std::vector<unsigned int>& m_indices, std::vector<Vertex>& m_vertices);
	void render();

	std::vector<unsigned int> m_indices;
	std::vector<Vertex> m_vertices;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;

	void create_Buffers();
};