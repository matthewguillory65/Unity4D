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

	int success = GL_FALSE;
	// check that it compiled and linked correctly
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE) {
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

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
