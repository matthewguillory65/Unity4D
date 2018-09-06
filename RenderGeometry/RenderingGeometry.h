#pragma once
#include "../Unity4D/MyApplication.h"
#include "Vertex.h"
#include <vector>
#include <GLM/glm/glm.hpp>
#include "../Unity4D/Transform.h"

class RenderingGeometry : public MyApplication
{
public:
	RenderingGeometry();
	~RenderingGeometry();
	std::vector<unsigned int> *m_indices;
	std::vector<Vertex> *m_vertices;
	unsigned int ibo;
	unsigned int vbo;
	unsigned int vao;
	unsigned int m_program;

	glm::mat4 m_model;
	glm::mat4 m_view;
	glm::mat4 m_projection;


	void Startup();
	void Shutdown();
	void Update(float dt);
	void Draw();
	void createBuffers();
	//ex. m_verticies of a square, A, B, C, D = {a, b, c, d}
	//ex. m_indecies for it would be, = {[0], [1], [2], [2], [3], [0]}
	
	//"gen, bind, buffer"
	//glGenBuffers("how many, 1", &m_vbo)
	//glBindBuffer("mode, GL_ArrayBuffer", m_vbo)
	//glBufferData(GL_Array_buffer, 4*32, m_verticies, GL_Static_draw)




};

