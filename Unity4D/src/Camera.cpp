#include "Camera.h"
#include "Transform.h"
Camera::Camera() : projectionTransform(glm::mat4(1)), viewTransform(glm::mat4(1))
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
	projectionTransform[3].z = -(2 * Far * Near / (Far - Near));
	auto expected = glm::perspective(fOv, aR, Near, Far);
	return projectionTransform;
}

glm::mat4 Camera::setOrthographic(float l, float r, float t, float b, float n, float f)
{
	projectionTransform[0].x = 2 / (r - l);
	projectionTransform[1].y = 2 / (t - b);
	projectionTransform[2].z = -2 / (f - n);
	projectionTransform[3].x = -((r + l) / (r - l));
	projectionTransform[3].y = -((t + b) / (t - b));
	projectionTransform[3].z = -((f + n) / (f - n));
	auto expected = glm::ortho(l, r, t, b, n, f);
	return projectionTransform;
}

glm::mat4 Camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 tmpr)
{
	glm::vec3 forward = glm::normalize(from - to);
	glm::vec3 right = glm::cross(normalize(tmpr), forward);
	glm::vec3 up = glm::cross(forward, right);

	viewTransform[0][0] = right.x;
	viewTransform[0][1] = right.y;
	viewTransform[0][2] = right.z;
	viewTransform[1][0] = up.x;
	viewTransform[1][1] = up.y;
	viewTransform[1][2] = -up.z;
	viewTransform[2][0] = forward.x;
	viewTransform[2][1] = -forward.y;
	viewTransform[2][2] = forward.z;

	viewTransform[3][0] = -from.x;
	viewTransform[3][1] = from.y;
	viewTransform[3][2] = -from.z;

	auto expected = glm::lookAt(glm::vec3(0, -20, 250), glm::vec3(0, 1, 10), glm::vec3(0, 1, 0));

	return viewTransform;
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
	m_view = translation;
	return m_view;
}