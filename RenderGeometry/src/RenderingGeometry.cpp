#define GLM_FORCE_SWIZZLE
#include "RenderingGeometry.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "Camera.h"

RenderingGeometry::RenderingGeometry()
{
}

float runningTime = 0;
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


	int np = 100;
	int nm = 100;
	mesh = new MeshRenderer();

	std::vector<glm::vec4> points = genHalfCircle(np, 5);

	points = rotateHalfCirlce(points, nm);

	std::vector<unsigned int> indices = getIndices(np, nm);

	std::vector<MeshRenderer::Vertex> vertexs;
	for (glm::vec4 point : points)
	{
		MeshRenderer::Vertex vertex = { point, glm::vec4(0, 1, 1, 1) };
		vertexs.push_back(vertex);
	}
	mesh->initialize(indices, vertexs);

	std::vector<unsigned int> cubeInd = getCubeIndices();
	std::vector<glm::vec4> cube = genCube();

	shader = new Shader();

	shader->load("shader.muh", Shader::SHADER_TYPE::VERTEX);
	shader->load("shader.fuh", Shader::SHADER_TYPE::FRAGMENT);

	//tex.load("Textures.png");

	shader->attach();

	movement = glm::mat4(1);
}

void RenderingGeometry::Shutdown()
{

}

Camera myCamera;
void RenderingGeometry::Update(float dt)
{
	
	m_model = glm::mat4(1);
	glm::vec3 eye = glm::vec3(0, -20, 250);
	//My Set Look At function
	m_view = myCamera.setLookAt(eye, glm::vec3(0, 1, 10), glm::vec3(0, 1, 0));
	//Switching between Perspective and Orthographic
	if (GetAsyncKeyState('V') & 0x8000)
	{
		m_projection = myCamera.setPerspective(90, 800 / (float)600, .1f, 1000.f);
	}
	if (GetAsyncKeyState('B') & 0x8000)
	{
		m_projection = myCamera.setOrthographic(-50, 50, -50, 50, 0.1f, 700);
	}
	//Rotation
	glm::mat4 rot = glm::rotate(glm::mat4(1), glm::cos(dt), glm::vec3(0, 1, 0));
	//m_model = m_model * rot * rot * rot * rot;
	runningTime = dt * 2;
}

void RenderingGeometry::Draw()
{
	glUseProgram(shader->m_program);
	shader->Bind();
	auto cameraPos = shader->getUniform("cameraPosition");
	auto varid = shader->getUniform("ProjectionViewWorld");
	auto lightDirection = shader->getUniform("lightDirection");
	auto lightColor = shader->getUniform("lightColor");
	auto lightPosition = shader->getUniform("lightPosition");

	glm::vec3 lP = glm::vec3( 1, 1, 0 );
	glm::vec3 lD = glm::vec3(-1, -1, 0);
	glm::vec3 camPosition = glm::vec3(0, -20, 200);
	glm::vec4 lC = glm::vec4(1, 1, 0, 1);
	lD *= glm::cos(runningTime);

	glUniform3fv(lightPosition, 1, &lP[0]);
	glUniform3fv(lightDirection, 1, &lD[0]);
	glUniform4fv(lightColor, 1, &lC[0]);
	glUniform3fv(cameraPos, 1, &camPosition[0]);

	int yPos = 100;
	int xMultiple = 0;

	//Values of how far to move
	glm::vec3 up(0, -.1, 0);
	glm::vec3 down(0, .1, 0);
	glm::vec3 right(-.1, 0, 0);
	glm::vec3 left(.1, 0, 0);
	glm::vec3 in(0, 0, .1);
	glm::vec3 out(0, 0, -.1);

	mesh->render();

	//Movement
	if (GetAsyncKeyState('W') & 0x8000)
	{
		movement *= myCamera.movement(up);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		movement *= myCamera.movement(down);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		movement *= myCamera.movement(right);
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		movement *= myCamera.movement(left);
	}
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		movement *= myCamera.movement(in);
	}
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		movement *= myCamera.movement(out);
	}

	//How many?
	for (int i = 1; i <= 1; i++)
	{
		glm::mat4 modelSixFour = glm::mat4(1);
		modelSixFour = glm::translate(modelSixFour, glm::vec3(0, 0, 0));
		modelSixFour = glm::translate(modelSixFour, glm::vec3(xMultiple * 2, yPos, 0));
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
{
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
	}
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

std::vector<unsigned int> RenderingGeometry::getCubeIndices()
{
	std::vector<unsigned int> indices =
	{	0, 1, 2, 2, 3, 0,//front
		3, 2, 4, 4, 5, 2,//Bot
		4, 5, 6, 6, 7, 4,//Back
		6, 7, 8, 8, 9, 6,//Top
		2, 1, 10, 10, 11, 2,//Right
		0, 3, 12, 12, 13, 0//Left
	};
	return indices;
}

std::vector<glm::vec4> RenderingGeometry::genCube()
{
	std::vector<glm::vec4> verts
		
	{																//Front
		(glm::vec4(0, 1, 1, 1), glm::vec4(1)),//0
		(glm::vec4(1, 1, 1, 1), glm::vec4(1)),//1
		(glm::vec4(1, 0, 1, 1), glm::vec4(1)),//2
		(glm::vec4(0, 0, 1, 1), glm::vec4(1)),//3
																	 //Bot
		(glm::vec4(0, 0, 0, 1), glm::vec4(1)),//4
		(glm::vec4(1, 0, 0, 1), glm::vec4(1)),//5
																	 //Back
		(glm::vec4(1, 1, 0, 1), glm::vec4(1)),//6
		(glm::vec4(0, 1, 0, 1), glm::vec4(1)),//7
																	 //Top
		(glm::vec4(0, 1, 1, 1), glm::vec4(1)),//8
		(glm::vec4(1, 1, 1, 1), glm::vec4(1)),//9
																 //Right
		(glm::vec4(1, 1, 0, 1), glm::vec4(1)),//10
		(glm::vec4(1, 0, 0, 1), glm::vec4(1)),//11
																 //Left
		(glm::vec4(0, 1, 0, 1), glm::vec4(1)),//12
		(glm::vec4(0, 0, 0, 1), glm::vec4(1))//13
	};
	return verts;
}