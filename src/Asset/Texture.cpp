#include "Asset/Texture.h"

#include <GLAD/glad.h>
#include <Render/stb_image.h>
#include <string>
#include <iostream>



Texture::Texture(const char* texturePath, std::string type) {

	//Change to load from file
	settings = TextureSettings(GL_REPEAT, GL_REPEAT, GL_NEAREST, GL_NEAREST);

	glGenTextures(1, &textureRef);

	glBindTexture(GL_TEXTURE_2D, textureRef);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1) {
			format = GL_RED;
		}
		else if (nrChannels == 3) {
			format = GL_RGB;
		}
		else if (nrChannels == 4) {
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture Failed to load" << std::endl;
	}
	stbi_image_free(data);

	this->type = type;
	this->path = texturePath;
}

unsigned int Texture::GetTextureID() {
	return textureRef;
}