#include "Texture.h"
#include "stb_image.h"

Texture::Texture()
{
	
}

Texture::~Texture()
{

}

bool Texture::load(const char * filename)
{
	data = stbi_load(filename, &imageWidth, &imageHeight, &imageFormat, STBI_rgb);


	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_glHandle);
	glBindTexture(GL_TEXTURE_2D, m_glHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return false;
}
void Texture::create(unsigned int width, unsigned int height, Format format, unsigned char * pixels)
{

}
