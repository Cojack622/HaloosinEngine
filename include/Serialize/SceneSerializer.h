#pragma once

#include "Core/Scene.h"
#include "Core/SystemManager.h"
#include "Asset/ModelLibrary.h"
#include "Asset/ShaderLibrary.h"


#include <entt/entity/registry.hpp>
#include <unordered_map>
#include <string>


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