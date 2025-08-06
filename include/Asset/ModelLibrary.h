#pragma once

#include "../Asset/Model.h"

#include <unordered_map>
#include <string>

class ModelLibrary {

public:
    Model* addModel(std::string modelName);

    void addModel(std::string modelName, Model* model) {
        models.insert({ modelName, model });
    }

    void removeModel(std::string modelName);

    Model* getModel(std::string modelName);

private:
    std::unordered_map<std::string, Model*> models;
};