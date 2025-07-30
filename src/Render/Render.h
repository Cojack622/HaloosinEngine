#pragma once

#include "Mesh.h"
#include "Asset/Shader.h"
#include "CoreComponents/CoreComponents.h"

enum Render_Mode {
	WIREFRAME,
	LIGHTING,
	NO_LIGHTING
};

class Renderer {
public:
	void RenderObject(Shader* shader, Mesh* mesh, c_Transform transform);

	//void ChangeRenderMode(Render_Mode mode);

private:
	glm::mat4 createModelMatrix(c_Transform);
	Render_Mode renderMode;
};