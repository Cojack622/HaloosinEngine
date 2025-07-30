#pragma once

#include <GLFW/glfw3.h>

struct Time {
public:
	float deltaTime;

	float CalculateTime() {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrameExecuted;
		lastFrameExecuted = currentFrame;
		return deltaTime;
	}
private:
	float lastFrameExecuted;
};