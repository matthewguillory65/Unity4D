#pragma once
#include <vector>
#include "MeshRenderer.h"
#include "Transform.h"
class MeshRender
{
public:
	MeshRender();
	~MeshRender();
	struct Vertex
	{
		glm::vec4 m_position;
		glm::vec4 m_color;
	};
	int Initialize(std::vector<unsigned int>, std::vector<Vertex>);
	int Render();
	
private: 
	std::vector<unsigned int> *m_indices;
	std::vector<Vertex> *m_vertices;
	unsigned int ibo;
	unsigned int vbo;
	unsigned int vao;
	int create_Buffers();

	//Not staying???
	unsigned int m_program;
	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;
};

