#pragma once

#include <glad/glad.h>
#include <gl/GL.h>

enum class TextureWrapping {
	Repeat = GL_REPEAT,
	MirroredRepeat = GL_MIRRORED_REPEAT,
	
	EdgeClamp= GL_CLAMP_TO_EDGE,
	BorderClamp = GL_CLAMP_TO_BORDER
};

enum class TextureFiltering {
	Nearest = GL_NEAREST,
	NearestNearest = GL_NEAREST_MIPMAP_NEAREST,
	NearestLinear = GL_NEAREST_MIPMAP_LINEAR,
	
	Linear = GL_LINEAR,
	LinearNearest = GL_LINEAR_MIPMAP_NEAREST,
	LinearLinear = GL_LINEAR_MIPMAP_LINEAR
};

class Texture
{
private:
	unsigned int m_TextureId;
	unsigned char* m_TextureData;

	int m_Width, m_Height, m_NrChannels;
	
	TextureWrapping m_WrapS;
	TextureWrapping m_WrapT;

	TextureFiltering m_MinFilter;
	TextureFiltering m_MagFilter;

	unsigned char* LoadTexture(const char* path, int* width_p, int* height_p, int* nrChannels_p);
public:

	Texture(const char* path, TextureWrapping wrapS,
		TextureWrapping wrapT, TextureFiltering minFilter, TextureFiltering magFilter);
	Texture(const char* path);
	~Texture();

	void Bind();
	void Unbind();
};