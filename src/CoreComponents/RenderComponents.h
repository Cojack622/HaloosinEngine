#pragma once

#include "Asset.h"
#include "Serializable.h"

#include "ShaderReference.h"
#include "ModelReference.h"


struct c_ModelRender {
	ShaderReference shader;
	ModelReference model;
};
COMPONENT(c_ModelRender)