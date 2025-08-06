#pragma once

#include "../Serialize/Serializable.h"
#include "../Math/Vector3.h"


struct c_DirectionalLight {
	Vector3 direction;
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
};
//COMPONENT(c_DirectionalLight)

struct c_PointLight{
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	Vector3 eq;
};
//COMPONENT(c_PointLight)