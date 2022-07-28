#pragma once

#include <stb/stb_image.h>
#include "GLFW/glfw3.h"

#include <iostream>

class Texture
{
public:
	GLuint textureID;
	Texture(const char* imagePath, bool alpha);
	~Texture();

	void bindTexture();
	void unbindTexture();
	void deleteTexture();
	void replaceTexture(const char* imagePath, bool alpha);
};

