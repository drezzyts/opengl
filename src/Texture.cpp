#include "Texture.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned char* Texture::LoadTexture(const char* path, int* width_p, int* height_p, int* nrChannels_p)
{
	unsigned char* data = stbi_load(path, width_p, height_p, nrChannels_p, 0);
	if (!data) 
	{
		std::cout << "[error]: Failed to load texture!" << std::endl;
	}
	else 
	{
		return data;
	}
}

Texture::Texture(const char* path, TextureWrapping wrapS, TextureWrapping wrapT, 
	TextureFiltering minFilter, TextureFiltering magFilter) :
	m_WrapS(wrapS), m_WrapT(wrapT), m_MinFilter(minFilter), m_MagFilter(magFilter)
{
	m_TextureData = Texture::LoadTexture(path, &m_Width, &m_Height, &m_NrChannels);
	
	glGenTextures(1, &m_TextureId);
	this->Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TextureData);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(const char* path) :
	m_WrapS(TextureWrapping::Repeat), m_WrapT(TextureWrapping::Repeat),
	m_MinFilter(TextureFiltering::LinearLinear), m_MagFilter(TextureFiltering::Linear)
{
	m_TextureData = Texture::LoadTexture(path, &m_Width, &m_Height, &m_NrChannels);

	glGenTextures(1, &m_TextureId);
	this->Bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_TextureData);
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
	stbi_image_free(m_TextureData);
	glDeleteTextures(1, &m_TextureId);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint) m_WrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint) m_WrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint) m_MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint) m_MagFilter);
}


void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

