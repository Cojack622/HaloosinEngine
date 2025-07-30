#pragma once
#include "Vector3.h"
namespace Tripe_Math {
    // Cross product returns a Vector3 perpendicular to the two input vectors
    inline Vector3 cross(Vector3 a, Vector3 b) {
        return Vector3(glm::cross(a.GetBaseVector(), b.GetBaseVector()));
    }

    // Normalize returns a unit vector in the same direction as input
    inline Vector3 normalize(Vector3 v) {
        return Vector3(glm::normalize(v.GetBaseVector()));
    }

    // Dot product returns a scalar, not a vector
    inline float dot(Vector3 a, Vector3 b) {
        return glm::dot(a.GetBaseVector(), b.GetBaseVector());
    }

    // Length returns the magnitude of the vector
    inline float length(Vector3 v) {
        return glm::length(v.GetBaseVector());
    }

    // Distance returns the distance between two points
    inline float distance(Vector3 a, Vector3 b) {
        return glm::distance(a.GetBaseVector(), b.GetBaseVector());
    }

    // Reflect returns the reflection of incident vector around normal
    inline Vector3 reflect(Vector3 I, Vector3 N) {
        return Vector3(glm::reflect(I.GetBaseVector(), N.GetBaseVector()));
    }

    // Refract returns the refraction vector
    inline Vector3 refract(Vector3 I, Vector3 N, float eta) {
        return Vector3(glm::refract(I.GetBaseVector(), N.GetBaseVector(), eta));
    }

    // Faceforward orients a vector to point away from the surface
    inline Vector3 faceforward(Vector3 N, Vector3 I, Vector3 Nref) {
        return Vector3(glm::faceforward(N.GetBaseVector(), I.GetBaseVector(), Nref.GetBaseVector()));
    }
}
