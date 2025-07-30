#include "ShaderLibrary.h"

/*______________________________________________________________________________*/

ShaderID ShaderLibrary::addShader(const std::string stringID, Shader shader) {
    //ShaderID id = shaders.size();

    shaders.push_back(shader);
    shaderNames.insert({ stringID, shader.ID });

    return shader.ID;
}

//Refactor later
void ShaderLibrary::removeShader(ShaderID id) {
    if (id >= shaders.size()) {
        //Assert methods here later
        return;
    }
    std::unordered_map<std::string, ShaderID>::iterator it = shaderNames.begin();
    shaders.erase(shaders.begin() + id);
    for (; it != shaderNames.end(); it++) {

        if ((*it).second == id) {
            shaderNames.erase(it);
        }
        else if ((*it).second > id) {
            (*it).second--;
        }
    }
}

void ShaderLibrary::removeShader(const std::string nameID) {
    removeShader(shaderNames[nameID]);
}

Shader* ShaderLibrary::getShader(ShaderID id) {
    for (auto it = shaders.begin(); it < shaders.end(); it++)
    {
        if (it->ID == id) {
            //What the fuck lmao
            return &(*it);
        }
    }

    return new Shader("", "");
    //Log error 
}

Shader* ShaderLibrary::getShader(const std::string nameID) {
    return getShader(shaderNames[nameID]);
}


