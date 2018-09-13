#include "MyApplication.h"
#include "../Dep/includes/Gizmos/Gizmos.h"
#include <iostream>

using glm::vec3;
using glm::vec4;
using glm::mat4;

GLFWwindow* window;
glm::mat4 m_model = glm::mat4(1);
float currentTime = glfwGetTime();
float prevTime = currentTime;
float dt = currentTime - prevTime;//dt = difference in time between frames
vec4 white(1);
vec4 black(0, 0, 0, 1);


MyApplication::MyApplication()
{
	
}


MyApplication::~MyApplication()
{
}

void MyApplication::run(const char * title, unsigned int width, unsigned int height, bool fullscreen)
{
	float prevTime = glfwGetTime();
	glfwInit();
	m_window = glfwCreateWindow(width, height, title, NULL, NULL);
	glfwMakeContextCurrent(m_window);
	ogl_LoadFunctions();
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	Startup();
	while (glfwWindowShouldClose(m_window) == false && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - prevTime;
		prevTime = currentTime;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Update(deltaTime);
		Draw();
		glfwSwapBuffers(m_window);
		glfwPollEvents();

	}

	Shutdown();
}

//int MyApplication::Startup()
//{
//	if (glfwInit() == false)
//		return -1;
//	//init glfw, make it a window by making it current context
//	window = glfwCreateWindow(1280, 720, "Unity4D", nullptr, nullptr);
//	glfwMakeContextCurrent(window);
//	ogl_LoadFunctions();
//	m_model = mat4(1);
//	camera = new FlyCamera();
//	camera->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
//	while (glfwWindowShouldClose(window) == false)
//	{
//		Draw();
//		Update();
//	}
//
//	return 0;
//}
//
//int MyApplication::Update()
//{
//	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
//	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
//
//	camera->setPosition(glm::vec3(10, 10, 10));
//
//	auto load = ogl_LoadFunctions();
//	auto major = ogl_GetMajorVersion();
//	auto minor = ogl_GetMinorVersion();
//	printf("GL: %i.%i\n", major, minor);
//
//	glClearColor(0.25f, 0.25f, 0.25f, 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
//	{
//
//		glClearColor(0.25f, 0.25f, 0.25f, 1);
//		glEnable(GL_DEPTH_TEST);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	
//
//	return 0;
//}
//
//int MyApplication::Draw()
//{
//	float dt;
//	glm::vec3 currentPosition = glm::vec3(0, 0, 0);
//
//	Gizmos::clear();
//
//	Gizmos::addTransform(glm::mat4(1));
//
//	for (int i = 0; i < 21; ++i)
//	{
//		Gizmos::addLine(vec3(-10 + i, 0, 10),
//			vec3(-10 + i, 0, -10),
//			i == 10 ? white : black);
//		Gizmos::addLine(vec3(10, 0, -10 + i),
//			vec3(-10, 0, -10 + i),
//			i == 10 ? white : black);
//	}
//
//	Gizmos::addSphere(glm::vec3(0, 0, 0), 5.f, 30, 30, glm::vec4(10, 0, 0, .5), &m_model);
//	Gizmos::draw(camera->getWorldTransform() * camera->getProjection() * camera->getView());
//	return 0;
//}