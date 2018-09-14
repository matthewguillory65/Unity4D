#define GLM_FORCE_SWIZZLE
#include "RenderingGeometry.h"
#include "Shader.h"

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
	MeshRenderer::Vertex a = { glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1) };
	MeshRenderer::Vertex b = { glm::vec4(10, 10, 0, 1), glm::vec4(0, 1, 0, 1) };
	MeshRenderer::Vertex c = { glm::vec4(10, -10, 0, 1), glm::vec4(0, 0, 1, 1) };
	MeshRenderer::Vertex d = { glm::vec4(-10, -10, 0, 1), glm::vec4(0, 0, 0, 1) };
	auto abcd = { glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1) };
	std::vector<MeshRenderer::Vertex>m_vertices = { a,b,c,d };
	std::vector<unsigned int>m_indices = { 0 ,1,2,2,3,0 };

	mesh = new MeshRenderer();
	mesh->initialize(m_indices, m_vertices);

	shader = new Shader();
	shader->defaultLoad();
}

void RenderingGeometry::Shutdown()
{
}

void RenderingGeometry::Update(float dt)
{
	m_model = glm::mat4(1);
	glm::vec3 eye = glm::vec3(0, -10, 20);
	m_view = glm::lookAt(eye, glm::vec3(0), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
}

void RenderingGeometry::Draw()
{
	glUseProgram(shader->m_program);
	shader->Bind();
	auto varid =  shader->getUniform("ProjectionViewWorld");

	glm::mat4 mvp = m_projection * m_view * m_model;

	glUniformMatrix4fv(varid, 1, GL_FALSE, &mvp[0][0]);

	mesh->render();
	shader->UnBind();

	glUseProgram(0);
}