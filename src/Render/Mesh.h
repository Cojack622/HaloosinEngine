#pragma once

#include "Asset/Texture.h"

#include <vector>
#include "Asset/Shader.h"



struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TexCoords;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;


	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	unsigned int GetVBO();
	unsigned int GetVAO();
	unsigned int GetEBO();

	void Draw(Shader& shader);

	//static std::vector<Vertex> CreateVertexMatrix(float* vbo);
private:
	//  render data
	void setupMesh();
	unsigned int VAO, VBO, EBO;
};

