#pragma once
#include <string>

#include "Scene.h"

#include "SystemManager.h"
#include "ModelLibrary.h"
#include "ShaderLibrary.h"


#include <entt/entity/registry.hpp>
#include <unordered_map>

class SceneSerializer {
public:
	void SerializeScene(entt::registry& reg, std::string sceneName);
	void DeserializeScene(Scene& s, std::string path);

private:

	void DeserializeProcedures(SystemManager& lib, std::string systemBlock);

	void DeserializeEntities(entt::registry& reg, std::string sceneName);

	void DeserializeModels(ModelLibrary& lib, std::string modelBlock);
	void DeserializeShaders(ShaderLibrary& lib, std::string shaderBlock);

	/*Map to track serialized components of an entity as the deserializer iterates through Component_Type pools*/
	std::unordered_map<entt::entity, std::vector<std::string>> entityComponents;
};