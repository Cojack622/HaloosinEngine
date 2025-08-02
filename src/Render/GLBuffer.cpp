#include "Render/GlBuffer.h"
#include "GLAD/glad.h"
#include "glm/glm.hpp"
#include <cstddef>
#include <iostream>

GLBuffer::GLBuffer(size_t size, unsigned int bindPoint) {
	binding = bindPoint;

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, bindPoint);

	glBindBufferRange(GL_UNIFORM_BUFFER, bindPoint, ubo, 0, size);

}


void GLBuffer::copyData(void* data, size_t copysize, size_t rangeStart) {
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferSubData(GL_UNIFORM_BUFFER, rangeStart, copysize, data);
	glBindBuffer(GL_UNIFORM_BUFFER, binding);
	if (glGetError() > 0) {
		std::cout << "Error Copying data to bind point" << binding << std::endl;
	}
}

unsigned int GLBuffer::getBinding() {
	return binding;
}