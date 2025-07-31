#include "SceneSerializer.h"

#include <rfl.hpp>
#include <rfl/json.hpp>
#include "entt/meta/resolve.hpp"

#include "SerialPrintHelpers.h"
#include "CoreComponents/CameraComponents.h"
#include "Serializable.h"
#include "SerializeProcedure.h"

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>


/*
* Serializes entity data in world register to a file
* @params reg
*		Registry with Entity component data
* @params sceneName
*		fileName to save serialized output to
*/

#define SUBSTRING_START 7 
#define ScenePath "Scene/"
void SceneSerializer::SerializeScene(entt::registry& reg, std::string sceneName) {

	std::string output = "";
	//For each component Type
	for (auto [id, storage] : reg.storage()) {


		auto component_Type = std::string(storage.type().name());
		auto stripped_Type = component_Type.substr(SUBSTRING_START);


		//For each entity in said type pool
		for (entt::entity e : storage) {

			//	//Save reference to components for this specific entity
			std::vector<std::string>& components = entityComponents[e];

			std::string serialized = (ComponentSerialize::SerializeFunctions[stripped_Type]).Serialize(storage.value(e));

			components.push_back(serialized);
		}
	}

	//Now each component is serialized, put it together sorted by entity
	unsigned int entityCounter = 0;
	for (auto e : entityComponents) {
		std::vector<std::string>& components = e.second;

		output += std::to_string(entityCounter) + ":[\n";


		//Add each serialized component to output
		for (std::string s : components) {
			output += s;
			output += ",\n";
		}


		output += "],\n";
		entityCounter++;
	}

	std::ofstream sceneFile(sceneName);
	sceneFile << output;
	sceneFile.close();
}


void SceneSerializer::DeserializeScene(Scene& s, std::string path) {
	std::ifstream InputFile(path);
	std::string block;

	std::string line;
	size_t closingBracketIndex = -1;



	const char* shaders = "<shaders>";
	const char* models = "<models>";
	const char* procedures = "<procedures>";
	const char* entities = "<entities>";

	while (getline(InputFile, line)) {



		if ((closingBracketIndex = line.find("</shaders>")) != -1) {
			size_t subStrStart = block.find(shaders) + strlen(shaders);
			DeserializeShaders(*s.shaders.get(), block.substr(subStrStart));
			block.clear();
		}
		else if ((closingBracketIndex = line.find("</models>")) != -1) {
			size_t subStrStart = block.find(models) + strlen(models);
			DeserializeModels(*s.models.get(), block.substr(subStrStart));
			block.clear();

		}
		else if ((closingBracketIndex = line.find("</procedures>")) != -1) {
			size_t subStrStart = block.find(procedures) + strlen(procedures);
			DeserializeProcedures(s.GetSystemManager(), block.substr(subStrStart));
			block.clear();

		}
		else if ((closingBracketIndex = line.find("</entities>")) != -1) {
			size_t subStrStart = block.find(entities) + strlen(entities);
			DeserializeEntities(s.world.registry, block.substr(subStrStart));
			block.clear();
		}
		else {
			block += line + "\n";
		}

	}

}

std::string trim(const std::string& str) {
	size_t start = str.find_first_not_of(" \t\r\n");
	if (start == std::string::npos) return "";
	size_t end = str.find_last_not_of(" \t\r\n");
	return str.substr(start, end - start + 1);
}


void SceneSerializer::DeserializeEntities(entt::registry& reg, std::string block) {
	std::istringstream InputFile(block);
	std::string entity;

	std::string line;
	while (getline(InputFile, line)) {

		line = trim(line);
		if (line.empty()) continue;

		size_t startPos = line.find_first_not_of("\t");
		if (line.substr(startPos).starts_with("],")) {

			entt::entity e = reg.create();

			std::regex componentRegex(R"((\w+):\(\s*([\s\S]*?)\),)", std::regex::ECMAScript);
			std::smatch match;

			std::string::const_iterator searchStart(entity.cbegin());
			while (std::regex_search(searchStart, entity.cend(), match, componentRegex)) {
				std::string components = match[2];
				components.erase(std::remove(components.begin(), components.end(), '\t'), components.end());
				(ComponentSerialize::SerializeFunctions[match[1]]).Deserialize(reg, e, components);

				searchStart = match.suffix().first;
			}


			entity = "";
		}
		else {
			entity += line;
		}
	}

}


void SceneSerializer::DeserializeShaders(ShaderLibrary& lib, std::string block) {
	std::istringstream stream(block);
	std::string line;

	while (std::getline(stream, line)) {
		line = trim(line);
		if (line.empty()) continue;

		std::istringstream lineStream(line);
		std::string vertexShader;
		std::string fragmentShader;
		std::string shaderName;

		bool succeed = std::getline(lineStream, vertexShader, ',') &&
			std::getline(lineStream, fragmentShader, ',') &&
			std::getline(lineStream, shaderName, ',');
		assert(succeed);


		lib.addShader(trim(shaderName), Shader(trim(vertexShader).c_str(), trim(fragmentShader).c_str()));


	}
}

void SceneSerializer::DeserializeModels(ModelLibrary& lib, std::string block) {
	std::istringstream stream(block);
	std::string line;

	while (std::getline(stream, line)) {
		line = trim(line);
		if (line.empty()) continue;

		size_t end = line.find_first_of(',', 0);
		lib.addModel(line.substr(0, end));
	}
}

void SceneSerializer::DeserializeProcedures(SystemManager& lib, std::string block) {
	std::istringstream stream(block);
	std::string line;

	while (std::getline(stream, line)) {
		line = trim(line);
		if (line.empty()) continue;

		size_t end = line.find_first_of(',', 0);
		lib.AddSystem(ProcedureSerialize::SerializeProcedures[line.substr(0, end)]);
	}
}