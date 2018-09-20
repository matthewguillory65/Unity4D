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
	FILE* file;
	err = fopen_s(&file, filename, "r");
	char buf[230];//creates a character buffer to store the line into
	while (std::fgets(buf, sizeof buf, file))
	{
		if (shadertype == 0)
		{
			vsSourceString.append(buf);
		}
		if (shadertype == 1)
		{
			fsSourceString.append(buf);
		}
	}
	if (shadertype == 0)
	{
		vsSource = vsSourceString.c_str();
	}
	if (shadertype == 1)
	{
		fsSource = fsSourceString.c_str();
	}


	//while (std::fgets(buf, sizeof buf, file))//go line by line
	//{
	//	data.append(buf);//add line to data
	//}
	//err = fclose(file);//close the file
	//const char* tmp = data.c_str();
	//switch (shadertype)
	//{
	//case Shader::SHADER_TYPE::VERTEX:
	//	
	//	break;
	//case Shader::SHADER_TYPE::FRAGMENT:
	//	memcpy(&fsSource, &tmp, 250);
	//	break;
	//}

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
