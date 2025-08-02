#include "Asset/ModelLibrary.h"

Model* ModelLibrary::addModel(std::string name) {
	models.insert({ name, new Model(name) });
	return models[name];
}

void ModelLibrary::removeModel(std::string name) {
	models.erase(name);
}

Model* ModelLibrary::getModel(std::string name) {
	return models[name];
}