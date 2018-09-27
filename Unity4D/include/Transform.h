#pragma once
#define GLM_FORCE_SWIZZLE

#include "GLM/glm/glm.hpp"
#include "GLM/glm/ext.hpp"

class Transform
{
public:
	Transform();
	~Transform();
	glm::mat4 Translate(glm::vec3 move);
	glm::mat4 MoveCamera(glm::vec3 move);
	glm::mat4 Rotate(float radians, glm::vec3 axis);
	glm::mat4 Scale(float size);
private:
	glm::mat4 m_model;//mat4
	glm::mat4 m_view;//mat4
	glm::vec3 m_worldPosition;//vec4
	glm::vec3 m_localPosition;//vec4
	glm::mat3 m_localRotation;//vec4
	glm::vec3 m_worldScale;//vec4
	glm::vec3 m_localScale;//vec4
protected:
	glm::mat3 m_worldRotation;//vec4
};

