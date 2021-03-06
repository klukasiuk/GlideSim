#include "texture.h"

#include "SOIL/SOIL.h"

Texture::Texture(char * texName)
{
	ID = SOIL_load_OGL_texture
	(
		"img.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}