#pragma once

#include <GLFW/glfw3.h>
#include "../GLAD/glad.h"

class WindowManager {
public:
	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	GLFWwindow* window;

	WindowManager(unsigned int w, unsigned int h);
	void Update();
	bool Close();
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
