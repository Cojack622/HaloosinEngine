#pragma once
#include "Asset/Shader.h"

class ShaderLibrary {
public:
    ShaderID addShader(std::string shaderName, Shader shader);

    void removeShader(ShaderID id);
    void removeShader(std::string stringID);

    Shader* getShader(ShaderID id);
    Shader* getShader(std::string stringID);

private:
    std::unordered_map<std::string, ShaderID> shaderNames;
    std::vector<Shader> shaders;


};