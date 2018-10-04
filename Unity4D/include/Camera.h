#pragma once
#define GLM_FORCE_SWIZZLE
class Transform;
#include <GLM/glm/glm.hpp>
#include "GLM/glm/ext.hpp"
class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 setPerspective(float fOv, float aR, float Near, float Far);
	glm::mat4 setOrthographic(float l, float r, float t, float b, float n, float f);
	//fOv = fieldOfview, aR = aspectRatio
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
	glm::mat4 movement(glm::vec3 move);
	glm::mat4 m_view;
protected:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

