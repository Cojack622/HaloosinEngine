#pragma once
#include "Core/Camera.h"
#include "Serialize/Serializable.h"


struct c_Camera {
    Camera camera;
    bool isPrimary;
};
COMPONENT(c_Camera)

