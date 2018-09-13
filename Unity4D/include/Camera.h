#pragma once
class Transform;
#include <GLM/glm/glm.hpp>
class Camera
{
public:
	Camera();
	~Camera();
	void setPerspective(float fOv, float aR, float Near, float Far);
	//fOv = fieldOfview, aR = aspectRatio
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	glm::mat4 getWorldTransform();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getProjectionView();
protected:
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectionViewTransform;
};

