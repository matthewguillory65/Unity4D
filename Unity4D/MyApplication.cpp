#include "MyApplication.h"
#include "Camera.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

GLFWwindow* window;
glm::mat4 m_model = glm::mat4(1);
float currentTime = glfwGetTime();
float prevTime = currentTime;
float dt = currentTime - prevTime;//dt = difference in time between frames


MyApplication::MyApplication()
{
	
}


MyApplication::~MyApplication()
{
}

int MyApplication::startUp()
{
	if (glfwInit() == false)
		return -1;

	window = glfwCreateWindow(1280, 720, "Unity4D", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	Gizmos::create();
	m_model = mat4(1);
	camera = new FlyCamera;
	camera->setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));	
	while (glfwWindowShouldClose(window) == false)
		Draw();
		Update();
		
	return 0;
}

int MyApplication::Update()
{
	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f);
	
	
	camera->setPosition(glm::vec3(10, 10, 10));

	auto load = ogl_LoadFunctions();
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);
	
	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	return 0;
}

int MyApplication::Draw()
{
	
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		
		glClearColor(0.25f, 0.25f, 0.25f, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec3 currentPosition = glm::vec3(0, 0, 0);

		Gizmos::clear();

		Gizmos::addTransform(glm::mat4(1));
		vec4 white(1);
		vec4 black(0, 0, 0, 1);

		for (int i = 0; i < 21; ++i)
		{
			Gizmos::addLine(vec3(-10 + i, 0, 10),
				vec3(-10 + i, 0, -10),
				i == 10 ? white : black);
			Gizmos::addLine(vec3(10, 0, -10 + i),
				vec3(-10, 0, -10 + i),
				i == 10 ? white : black);
		}

		Gizmos::addSphere(glm::vec3(0, 0, 0), 5.f, 30, 30, glm::vec4(10, 0, 0, .5), &m_model);
		camera->update(dt);
		Gizmos::draw(camera->getWorldTransform() * camera->getProjection() * camera->getView());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}