#pragma once
#include "gl_core_4_4.h"
#include "../Dep/includes/GLFW32/glfw3.h"
#include "FlyCamera.h"

class MyApplication
{
public:
	MyApplication();
	~MyApplication();
	
	int startUp(const char * title, unsigned int width, unsigned int height, bool fullscreen);

	int Update();

	int Draw();

	FlyCamera* camera;
};

