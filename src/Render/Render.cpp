#include <GLAD/glad.h>

#include "Render/Render.h"
#include "Asset/Shader.h"
#include "CoreComponents/CoreComponents.h"

#include <string>



void Renderer::RenderObject(Shader* shader, Mesh* mesh, c_Transform transform) {

    shader->use();

    shader->setFloat("material.shininess", 64);
    shader->setMat4("u_Model", createModelMatrix(transform));

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < (unsigned int)mesh->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = mesh->textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader->setInt(("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, mesh->textures[i].GetTextureID());
    }
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(mesh->GetVAO());

    glDrawElements(GL_TRIANGLES, (GLsizei)mesh->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::mat4 Renderer::createModelMatrix(c_Transform transform) {
    glm::mat4 model = glm::mat4(1.0);
    //model = glm::translate(model, transform.translate);
    //model = glm::scale(model, transform.scale);

    //model = glm::mat4_cast(glm::quat(transform.rotation)) * model;

    return model;
}