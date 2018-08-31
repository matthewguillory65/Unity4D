#pragma once
#include <iostream>
#include "gl_core_4_4.h"
#include "glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/ext.hpp"
#include "Gizmos.h"
#include "FlyCamera.h"
class MyApplication
{
public:
	MyApplication();
	~MyApplication();
	
	int startUp();

	int Update();

	int Draw();

	FlyCamera* camera;
};

