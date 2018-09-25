#define GLM_FORCE_SWIZZLE
#include <iostream>
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
	/*MeshRenderer::Vertex a = { glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1) };
	MeshRenderer::Vertex b = { glm::vec4(10, 10, 0, 1), glm::vec4(0, 1, 0, 1) };
	MeshRenderer::Vertex c = { glm::vec4(10, -10, 0, 1), glm::vec4(0, 0, 1, 1) };
	MeshRenderer::Vertex d = { glm::vec4(-10, -10, 0, 1), glm::vec4(0, 0, 0, 1) };
	auto abcd = { glm::vec4(-10, 10, 0, 1), glm::vec4(1, 0, 0, 1) };
	std::vector<MeshRenderer::Vertex>m_vertices = { a,b,c,d };
	std::vector<unsigned int>m_indices = { 0 ,1,2,2,3,0 };*/
	int np = 100;
	int nm = 100;
	mesh = new MeshRenderer();

	std::vector<glm::vec4> points = genHalfCircle(np, 5);

	points = rotateHalfCirlce(points, nm);

	std::vector<unsigned int> indices = getIndices(np, nm);

	std::vector<MeshRenderer::Vertex> vertexs;
	for (glm::vec4 point : points)
	{
		MeshRenderer::Vertex vertex = { point, glm::vec4(1, 1, 1, 1) };
		vertexs.push_back(vertex);
	}
	mesh->initialize(indices, vertexs);

	shader = new Shader();

	shader->load("shader.muh", Shader::SHADER_TYPE::VERTEX);
	shader->load("shader.fuh", Shader::SHADER_TYPE::FRAGMENT);

	shader->attach();

	movement = glm::mat4(1);
}

void RenderingGeometry::Shutdown()
{

}

void RenderingGeometry::Update(float dt)
{
	m_model = glm::mat4(1);
	glm::vec3 eye = glm::vec3(0, -20, 200);
	m_view = glm::lookAt(eye, glm::vec3(0, 1, 10), glm::vec3(0, 1, 0));
	m_projection = glm::perspective(glm::quarter_pi<float>(), 800 / (float)600, 0.1f, 1000.f);
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::cos(dt), glm::vec3(0, 1, 0));
	m_model = m_model * rot * rot * rot * rot;
}

void RenderingGeometry::Draw()
{
	glUseProgram(shader->m_program);
	shader->Bind();
	auto varid = shader->getUniform("ProjectionViewWorld");

	int yPos = 100;
	int xMultiple = 0;

	//Values of how far to move
	Transform transform;
	glm::vec3 up(0, 1, 0);
	glm::vec3 down(0, -1, 0);
	glm::vec3 right(1, 0, 0);
	glm::vec3 left(-1, 0, 0);
	glm::vec3 in(0, 0, 1);
	glm::vec3 out(0, 0, -1);

	mesh->render();

	//Movement
	if (GetAsyncKeyState('W') & 0x8000)
	{
		movement *= transform.Translate(up);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		movement *= transform.Translate(down);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		movement *= transform.Translate(right);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		movement *= transform.Translate(left);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		movement *= transform.Translate(in);
	}
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		movement *= transform.Translate(out);
	}

	//How many?
	for (int i = 1; i <= 1; i++)
	{
		glm::mat4 modelSixFour = glm::mat4(1);
		modelSixFour = glm::translate(modelSixFour, glm::vec3(0, 0, 0));
		modelSixFour = glm::translate(modelSixFour, glm::vec3(xMultiple * 20, yPos, 0));
		modelSixFour = glm::mat4(1) * glm::scale(glm::mat4(1), glm::vec3(20, 20, 20));
		glm::mat4 mvpSixFour = m_projection * m_view * modelSixFour * movement * m_model;
		glUniformMatrix4fv(varid, 1, GL_FALSE, &mvpSixFour[0][0]);
		mesh->render();
		xMultiple++;
		if (xMultiple == 10)
		{
			yPos -= 20;
			xMultiple = 0;
		}
	}

	shader->UnBind();
	glUseProgram(0);
}
float runningTime = 0;
std::vector<glm::vec4> RenderingGeometry::genHalfCircle(int np, int radius)
{
	std::vector<glm::vec4> points;
	float slice = glm::pi<float>() / (float)(np-1);
	
	for(int i = 0; i < np; i++)
	{
		float theta = i * slice;
		points.push_back(glm::vec4(radius*glm::cos(theta), radius*glm::sin(theta), 0, 1));
	}

	return points;
}

std::vector<unsigned int> RenderingGeometry::getIndices(int np, int nm)
{//u stay away from hyeah
	std::vector<unsigned int> indices;
	int y = 0;

	for (int j = 0; j < nm; j++)
	{
		for (int i = 0; i < np; i++)
		{
			indices.push_back(y);
			indices.push_back(y + np);
			y++;
		}
		indices.push_back(0xFFFF);
	}//u stay away from hyeah
	return indices;
}

std::vector<glm::vec4> RenderingGeometry::rotateHalfCirlce(std::vector<glm::vec4> points, unsigned int nm)
{
	std::vector<glm::vec4> allPoints;
	for (int i = 0; i <= nm; i++)
	{
		float slice = 2.0f * glm::pi<float>() / (float)nm ;
		float theta = i * slice;
		for (int j = 0; j < points.size(); j++)
		{
			float newX = points[j].x;
			float newY = points[j].y * cos(theta) + points[j].z * -sin(theta);
			float newZ = points[j].z * cos(theta) + points[j].y * sin(theta);
			allPoints.push_back(glm::vec4(newX, newY, newZ, 1));
			//allPoints[i] = glm::round(allPoints[i]);
		}
	}
	return allPoints;
}

//2	6	9	12	15
//1	5	8	11	14			number of maridians = nm
//0	4	7	10	13
//0, 3, 1, 4, 2, 5, 0xFFFF
//
//2__5
//|\ |
//|	\|
//1__4
//|\ |
//|	\|
//0__3
//Here we would need to start over
//bot_left = i;
//bot_right = i + np; np = numberofPoints