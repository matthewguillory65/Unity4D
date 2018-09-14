#pragma once
class GLFWwindow;
class FlyCamera;
class MyApplication
{
public:
	MyApplication();
	~MyApplication();
	void run(const char * title, unsigned int width, unsigned int height, bool fullscreen);
	virtual void Startup() = 0;
	virtual void Shutdown() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	GLFWwindow* m_window;
	FlyCamera* camera;
	
};

