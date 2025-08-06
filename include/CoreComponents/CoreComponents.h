#pragma once

#include "../Serialize/Serializable.h"


#include "../Math/Vector3.h"


struct c_Transform {
	Vector3 translate;
	Vector3 rotation;
	Vector3 scale;
};
COMPONENT(c_Transform)
