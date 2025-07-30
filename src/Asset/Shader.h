#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include <string>
#include <unordered_map>

typedef unsigned int ShaderID;

struct Material {
    unsigned int diffuse;
    unsigned int specular;
    float shininess;
};



class Shader
{
public:
    // the program ID
    unsigned int ID;

    //Temporary solution to have Shaders store their shadername 

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMat4(const std::string& name, glm::mat4 value) const;
    void setVec3(const std::string& name, glm::vec3 value) const;
    //Setup is to bind location of certain UBO's
    void (*setup)(ShaderID id);


private:
    void checkCompileErrors(unsigned int shader, std::string type);
};




