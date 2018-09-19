#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <stdio.h>
#include "Shader.h"
#include <fstream>




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

bool Shader::load(const char * filename, Shader::SHADER_TYPE shadertype)
{
	errno_t err;
	FILE *file; //create a filestream	
	std::string data;//create a variable to store the file info line by line

	char buf[500];//creates a character buffer to store the data into
	err = fopen_s(&file, filename, "r");//open the file  in read mode

	while (std::fgets(buf, sizeof buf, file))//go line by line
	{
		data.append(buf);//add line to data
	}
	err = fclose(file);//close the file

	switch (shadertype)
	{
	case Shader::SHADER_TYPE::VERTEX:
		vsSource = data.c_str();//we need to 
		
		break;
	case Shader::SHADER_TYPE::FRAGMENT:
		fsSource = data.c_str();
		break;
	}
	
	
	return data.length() > 0;
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
