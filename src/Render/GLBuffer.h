#pragma once

class GLBuffer {
public:
	GLBuffer(size_t size, unsigned int bindPoint);
	unsigned int getBinding();


	void copyData(void* data, size_t copySize, size_t rangeStart);

private:
	unsigned int ubo = 0;
	unsigned int binding;
};