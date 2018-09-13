#include "Transform.h"

Transform::Transform()
{
	m_model = glm::mat4(1);
	m_worldPosition = m_model[3];
	m_localPosition = m_model[3];
	for (int col = 0; col < 3; col++)
	{
		m_worldRotation[col] = m_model[col].xyz;
		m_localRotation[col] = m_model[col].xyz;
	}
	m_worldScale = glm::vec3(1, 1, 1);
	m_localScale = glm::vec3(1, 1, 1);
}

Transform::~Transform()
{
}

glm::mat4 Transform::Translate(glm::vec3 move)
{
	glm::mat4 translation = glm::mat4(1);
	translation[3].xyz = move;
	m_model = m_model * translation;
	return m_model;
}

glm::mat4 Transform::Rotate(float radians, glm::vec3 axis)
{
	auto cosine = cos(radians);
	auto sine = sin(radians);
	auto xCol = glm::vec4(1, -sine, cosine, 0);
	auto yCol = glm::vec4(cosine, 1, -sine, 0);
	auto zCol = glm::vec4(-sine, cosine, 1, 0);
	
	if (axis == glm::vec3(1, 0, 0))
	{
		//When rotating on the x-axis, the x-axis will not move
		m_model[1].y = cosine;
		m_model[1].z = -sine;
		m_model[2].y = cosine;
		m_model[2].z = sine;
	}

	if (axis == glm::vec3(0, 1, 0))
	{
		//When rotating on the y-axis, the y-axis will not move
		m_model[0].x = cosine;
		m_model[0].z = -sine;
		m_model[2].x = sine;
		m_model[2].z = cosine;
	}

	if (axis == glm::vec3(0, 0, 1))
	{
		//When rotating on the z-axis, the z-axis will not move
		m_model[1].x = -sine;
		m_model[1].y = cosine;
		m_model[0].x = sine;
		m_model[0].y = cosine;
	}
	return m_model;
}

glm::mat4 Transform::Scale(float size)
{
	glm::mat4 scale = glm::mat4(1);
	m_model = m_model * size;
	scale[0].x = size;
	scale[1].y = size;
	scale[2].z = size;
	return m_model;
}
