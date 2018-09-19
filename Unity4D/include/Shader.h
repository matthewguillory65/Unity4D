#pragma once
#include "gl_core_4_4.h"
#include "Transform.h"
#include "MeshRenderer.h"

class Shader
{
public:
	Shader();
	~Shader();
	enum SHADER_TYPE
	{
		VERTEX = 0, FRAGMENT = 1
	};
	void Bind();
	void UnBind();
	bool load(const char* filename, Shader::SHADER_TYPE shadertype);
	bool attach();
	void defaultLoad();
	//void Load();

	struct ShaderData
	{
		Shader *shader;
		char *source;
		unsigned type;
		bool isFile;
	};

	unsigned int getUniform(const char*);
	unsigned int vertexShader;
	unsigned int fragmentShader;

	const char* vsSource;
	const char* fsSource;
	std::string vsSourceString;
	std::string fsSourceString;

	unsigned int m_program;
};