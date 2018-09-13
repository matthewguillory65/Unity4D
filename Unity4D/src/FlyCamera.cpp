#include <iostream>
#include "FlyCamera.h"
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
	auto window = glfwGetCurrentContext();
	auto currentPosition = glm::vec3(getWorldTransform()[3].x, getWorldTransform()[3].y, getWorldTransform()[3].z);

	if (glfwGetKey(window, GLFW_KEY_W))
	{
		setPosition(currentPosition.y + glm::vec3(0, 0, speed) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		setPosition(currentPosition.y - glm::vec3(0, 0, speed) * dt);
		std::cout << "HI" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		setPosition(currentPosition.x - glm::vec3(speed, 0, 0) * dt);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		setPosition(currentPosition.x + glm::vec3(speed, 0, 0) * dt);
	}

	projectionViewTransform = viewTransform * projectionViewTransform;
}

