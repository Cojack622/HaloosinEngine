#pragma once
#include "Camera.h"
#include "Serializable.h"


struct c_Camera {
    Camera camera;
    bool isPrimary;
};
COMPONENT(c_Camera)

