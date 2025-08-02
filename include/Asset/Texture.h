#pragma once

#include <string>

class Texture {
public:

	struct TextureSettings {
		int wrapS;
		int wrapT;
		int minFilter;
		int maxFilter;
	} settings;

	Texture(const char* texturePath, std::string type);
	std::string type;
	std::string path;
	unsigned int GetTextureID();

private:
	unsigned int textureRef;
};