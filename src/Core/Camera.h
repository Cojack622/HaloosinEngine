#pragma once


#include <glm/glm.hpp>

#include "math/Vector3.h"

#include "Serialize/Serializable.h"
#include "Serialize/Reflector.h"

enum class Camera_Type {
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera : Serializable {
private:
	Camera_Type camType;
	float zoom, near, far;
	float aspectRatio;

	void calculate_Projection();

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Vector3 Up, Front;

public:

	struct SerializedFields {
		Camera_Type* camType;
		float* zoom;
		float* near;
		float* far;
		float* aspectRatio;
	};

	const Vector3 World_Up = Vector3(0.0, 1.0, 0.0);
	Camera() {};

	Camera(Camera_Type type, float zoom, float aspectRatio, float near, float far);
	void OnInit();

	glm::mat4 View_Projection_Matrix();
	void Update_View(c_Transform transform);
	void Update_Projection(float aspectRatio);

	Vector3 getUpVector() {
		return Up;
	}

	Vector3 getFrontVector() {
		return Front;
	}

	SerializedFields* Get_Accessor() {
		//Could be aggregated but visual studio got mad at me s
		return new SerializedFields{ .camType = &camType,
			.zoom = &zoom,
			.near = &near,
			.far = &far,
			.aspectRatio = &aspectRatio
		};
	}


};

