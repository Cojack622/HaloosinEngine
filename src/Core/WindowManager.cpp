#include "Core/WindowManager.h"
#include <iostream>

WindowManager::WindowManager(unsigned int w, unsigned int h) : SCR_WIDTH(w), SCR_HEIGHT(h) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Vita Mechanica", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);

    glfwSetKeyCallback(window, keyCallback);

}

void WindowManager::Update() {
    glfwSwapBuffers(window);
    glfwPollEvents();

}

bool WindowManager::Close() {
    if (glfwWindowShouldClose(window)) {
        glfwTerminate();
        return true;
    }
    return false;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}




