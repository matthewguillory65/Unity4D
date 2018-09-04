#pragma once
#include "Vertex.h"
#include <vector>
#include <GLM/glm.hpp>

class RenderingGeometry
{
public:
	RenderingGeometry();
	~RenderingGeometry();
	std::vector<unsigned int> *m_indices;
	std::vector<Vertex> *m_vertices;
	unsigned int ibo;
	unsigned int vbo;
	unsigned int vao;
	void Startup();
	//ex. m_verticies of a square, A, B, C, D = {a, b, c, d}
	//ex. m_indecies for it would be, = {[0], [1], [2], [2], [3], [0]}
	
	//"gen, bind, buffer"
	//glGenBuffers("how many, 1", &m_vbo)
	//glBindBuffer("mode, GL_ArrayBuffer", m_vbo)
	//glBufferData(GL_Array_buffer, 4*32, m_verticies, GL_Static_draw)




};

