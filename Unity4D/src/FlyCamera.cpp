#define GLM_FORCE_SWIZZLE
#include <iostream>
#include "FlyCamera.h"
#include "Transform.h"
#include <GLM/glm/glm.hpp>
#include "GLFW32/glfw3.h"



FlyCamera::FlyCamera()
{
	worldTransform = glm::mat4{ 1 };
}


FlyCamera::~FlyCamera()
{

}

void FlyCamera::update(float dt)
{
	Transform transform;
	glm::vec3 up(0, 1, 0);
	glm::vec3 down(0, -1, 0);
	glm::vec3 right(1, 0, 0);
	glm::vec3 left(-1, 0, 0);
	glm::vec3 in(0, 0, 1);
	glm::vec3 out(0, 0, -1);
 
	auto window = glfwGetCurrentContext();
	
	auto currentPosition = glm::vec3(getWorldTransform()[3].x, getWorldTransform()[3].y, getWorldTransform()[3].z);

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		movement *= transform.Translate(up);
		//setPosition(currentPosition.y + glm::vec3(0, 0, speed) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		movement *= transform.Translate(down);
		//setPosition(currentPosition.y - glm::vec3(0, 0, speed) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		movement *= transform.Translate(right);
		//setPosition(currentPosition.x - glm::vec3(speed, 0, 0) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		movement *= transform.Translate(left);
		//setPosition(currentPosition.x + glm::vec3(speed, 0, 0) * dt);
	}

	projectionViewTransform = viewTransform * projectionTransform;
}

