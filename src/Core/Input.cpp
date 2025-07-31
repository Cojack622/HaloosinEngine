#include "Input.h"

#include <fstream>
#include "Logger/Logger.h"

void InputManager::loadInputFile(GLFWwindow* window, std::string path) {
    InputManager::window = window;

    std::ifstream file(path);

    if (!file.is_open()) {
        LOG_ERROR("IO ERROR::COULD NOT OPEN INPUT FILE");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        // Find the position of the colon
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            // Extract key and value
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);

            // Add to map
            actionToKey[key] = std::stoi(value);
        }
    }

    file.close();
}

bool InputManager::getInputPressed(std::string input) {
    //Later on check to make sure input type is allowed 

    //int key = actionToKey[input];
    int state = glfwGetKey(window, actionToKey[input]);
    return state == GLFW_PRESS;
}

bool InputManager::getInputReleased(std::string input) {
    int state = glfwGetKey(window, actionToKey[input]);
    return state == GLFW_RELEASE;
}