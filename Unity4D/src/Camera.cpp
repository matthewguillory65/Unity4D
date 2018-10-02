#include "Camera.h"
#include "Transform.h"
Camera::Camera()
{
	setPerspective(glm::pi<float>(), 16/9, .1, 1000.f);
}


Camera::~Camera()
{

}

glm::mat4 Camera::setPerspective(float fOv, float aR, float Near, float Far)
{
	projectionTransform[0].x = 1 / (aR * tan(fOv / 2));
	projectionTransform[1].y = 1 / tan(fOv / 2);
	projectionTransform[2].z = -((Far + Near) / (Far - Near));
	projectionTransform[2].w = -1;
	projectionTransform[3].z = -(2 * Far*Near / (Far - Near));
	return projectionTransform;
}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	glm::lookAt(from, to, up);
}

void Camera::setPosition(glm::vec3 position)
{
	worldTransform[3].x = position.x;
	worldTransform[3].y = position.y;
	worldTransform[3].z = position.z;
}

glm::mat4 Camera::getWorldTransform()
{
	return this->worldTransform;
}

glm::mat4 Camera::getView()
{
	return this->viewTransform;
}

glm::mat4 Camera::getProjection()
{
	return this->projectionTransform;
}

glm::mat4 Camera::getProjectionView()
{
	return this->projectionViewTransform;
}

glm::mat4 Camera::movement(glm::vec3 move)
{
	glm::mat4 translation = glm::mat4(1);
	translation[3].xyz = move;
	m_view = m_view * translation;
	return m_view;
}