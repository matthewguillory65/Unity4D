#include "RenderingGeometry.h"
#include <gl_core_4_4.h>

RenderingGeometry::RenderingGeometry()
{
	
}


RenderingGeometry::~RenderingGeometry()
{

}

//  A _____ D
//	 |\    |
//	 | \   |
//	 |  \  |
//	 |	 \ |
//	 |____\|
//  B		C

void RenderingGeometry::Startup()
{
	Vertex A(glm::vec4(-10, 10, 0, 0));
	Vertex B(glm::vec4(-10, -10, 0, 0));
	Vertex C(glm::vec4(10, -10, 0, 0));
	Vertex D(glm::vec4(10, 10, 0, 0));

	m_vertices = new std::vector<Vertex>{ A, B, C, D };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 128, m_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_indices = new std::vector<unsigned int>{ 0, 1, 2, 2, 3, 0 };
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec4));

}