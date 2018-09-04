#pragma once
#include "gl_core_4_4.h"
#include "glfw3.h"
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

