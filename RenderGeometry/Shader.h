#include "gl_core_4_4.h"
#include "Transform.h"
#include "MeshRenderer.h"
#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	void Bind();
	void UnBind();
	bool load(const char* filename, unsigned int type, bool isFile = true);
	bool attach();
	void defaultLoad();
	//void Load();

	unsigned int getUniform(const char*);
	unsigned int vertexShader;
	unsigned int fragmentShader;

	const char* vsSource;
	const char* fsSource;

	unsigned int m_program;
};

struct ShaderData
{
	Shader *shader;
	char *source;
	unsigned type;
	bool isFile;
};