#pragma once
#define STD_IMAGE_IMPLEMENTATION
#include <string>

#include "Shader.h"



// a class for wrapping up an opengl texture image
class Texture {
public:

	enum Format : unsigned int {
		RED = 1,
		RG,
		RGB,
		RGBA
	};

	Texture();
	Texture(const char* filename);
	Texture(unsigned int width, unsigned int height, Format format, unsigned char* pixels = nullptr);
	virtual ~Texture();

	// load a jpg, bmp, png or tga
	bool load(const char* filename);

	// binding a jpg, bmp, png or tga
	void bind(unsigned int slot)const;

	// creates a texture that can be filled in with pixels
	void create(unsigned int width, unsigned int height, Format format, unsigned char* pixels = nullptr);

	// returns the filename or "none" if not loaded from a file
	const std::string& getFilename() const { return m_filename; }

	// returns the opengl texture handle
	unsigned int getHandle() const { return m_glHandle; }

	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }
	unsigned int getFormat() const { return m_format; }
	const unsigned char* getPixels() const { return m_loadedPixels; }

	MeshRenderer mesh;
	Shader shader;
	int imageWidth, imageHeight, imageFormat;
	unsigned char* data;

protected:

	std::string		m_filename;
	unsigned int	m_width;
	unsigned int	m_height;
	unsigned int	m_glHandle;
	unsigned int	m_format;
	unsigned char*	m_loadedPixels;
};