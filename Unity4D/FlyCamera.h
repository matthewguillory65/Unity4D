#pragma once
#include "Camera.h"
#include <glm/glm.hpp>
class FlyCamera : public Camera
{
public:
	FlyCamera();
	~FlyCamera();
	void update(float dt);
private:
	float speed;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 out;
};

