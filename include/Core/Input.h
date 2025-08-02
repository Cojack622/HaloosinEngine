#pragma once

#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>

//High level Input manager that maps General Input "actions" to keys
//Should read input mappings from file
class InputManager {
private:
	//Change this later to have Variable input
	inline static std::unordered_map<std::string, unsigned int> actionToKey;
	inline static GLFWwindow* window;

public:

	static void loadInputFile(GLFWwindow* window, std::string path);
	static bool getInputPressed(std::string action);
	static bool getInputReleased(std::string action);

	InputManager() = delete;
};