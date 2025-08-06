#pragma once


#include "../Serialize/Serializable.h"

#include "../Asset/ShaderReference.h"
#include "../Asset/ModelReference.h"


struct c_ModelRender {
	ShaderReference shader;
	ModelReference model;
};
COMPONENT(c_ModelRender)