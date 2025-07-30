#pragma once

#include <vector>
#include <iostream>

#include "Shader.h"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../Render/Mesh.h"


//Probably should change this to load from file
#define MODEL_FILE_PATH "models/"
#define MODEL_FILE_TYPE ".obj"

class Model {
private:
	std::string modelName;
	std::string directory;

public:
	Model() {};

	Model(std::string name) {
		modelName = std::string(name);
		directory = std::string(MODEL_FILE_PATH) + modelName + "/" + modelName + MODEL_FILE_TYPE;

		loadModel(directory);
	}

	std::string GetModelName() {
		return modelName;
	}

	void Draw(Shader& shader);

private:
	std::vector<Mesh> meshes;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	//void processNode(aiNode *node, const aiScene *scene);
};

//namespace ComponentSerialize {
//	Reflector<Model> r_Model;
//}