#include <iostream>
#include <fstream>
#include "Shader.h"


Shader::Shader()
{
	m_program = glCreateProgram();
}

Shader::~Shader()
{
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

bool Shader::load(const char * filename[])
{
	std::fstream file;
	file.open(filename);
	if (file.is_open() == true)
	{
		file.read(filename, 256);
		std::cout << "the file be open" << std::endl;
	}

	file.close();
	if (file.is_open() == false)
	{
		std::cout << "the file be closed" << std::endl;
	}
	return false;
}

bool Shader::attach()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	
	return true;
}

void Shader::defaultLoad()
{
	
	vsSource = "#version 410\n \
		                    layout(location = 0) in vec4 Position; \
                            layout(location = 1) in vec4 Color; \
                            out vec4 vColor; \
                            uniform mat4 ProjectionViewWorld; \
                            void main() { vColor = Color; \
                            gl_Position = ProjectionViewWorld * Position; }";

	fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vColor; }";
	this->attach();
}

unsigned int Shader::getUniform(const char *name)
{
	return glGetUniformLocation(m_program, name);
}
