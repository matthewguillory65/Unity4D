#include "Shader.h"

Shader::Shader()
{
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

bool Shader::load(const char * filename, unsigned int type, bool isFile)
{
	filename = "ProjectionViewWorld";
	m_program = glCreateProgram();

	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);
	return isFile;
}

bool Shader::attach()
{
	glShaderSource(vertexShader, 1, (const char**)vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)fsSource, 0);
	glCompileShader(fragmentShader);	
	return false;
}

void Shader::defaultLoad()
{

	const char*	vsSource = "#version 410\n \
		                        layout(location = 0) in vec4 Position; \
                            layout(location = 1) in vec4 Color; \
                            out vec4 vColor; \
                            uniform mat4 ProjectionViewWorld; \
                            void main() { vColor = Color; \
                            gl_Position = ProjectionViewWorld * Position; }";

	const char *fsSource = "#version 410\n \
                            in vec4 vColor; \
                            out vec4 FragColor; \
                            void main() { FragColor = vColor; }";
}

unsigned int Shader::getUniform(const char *)
{
	
	return 0;
}