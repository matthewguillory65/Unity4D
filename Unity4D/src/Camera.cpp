#include "Camera.h"
#include "Transform.h"
Camera::Camera()
{
	setPerspective(glm::pi<float>() * .25f, 16/9, .1, 1000);
}


Camera::~Camera()
{

}

void Camera::setPerspective(float fOv, float aR, float Near, float Far)
{
	glm::perspective(fOv, aR, Near, Far);
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
