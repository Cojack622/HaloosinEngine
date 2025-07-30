#include "Camera.h"

#include "CoreComponents/CoreComponents.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Math/VectorMath.h"

Camera::Camera(Camera_Type type, float zoom, float aspectRatio, float near, float far) {
	this->zoom = zoom;
	this->near = near;
	this->far = far;

	this->camType = type;
	this->aspectRatio = aspectRatio;

	OnInit();
}

void Camera::OnInit() {
	viewMatrix = glm::mat4(0.0f);

	calculate_Projection();
}

void Camera::Update_Projection(float aspectRatio) {
	this->aspectRatio = aspectRatio;
	calculate_Projection();
}

void Camera::Update_View(c_Transform transform) {
	Vector3 front(0.0f);
	front.x(cos(glm::radians(transform.rotation.y())) * cos(glm::radians(transform.rotation.x())));
	front.y(sin(glm::radians(transform.rotation.x())));
	front.z(sin(glm::radians(transform.rotation.y())) * cos(glm::radians(transform.rotation.x())));
	Front = Tripe_Math::normalize(front);

	Vector3 Right = Tripe_Math::normalize(Tripe_Math::cross(Front, World_Up));
	Up = Tripe_Math::normalize(Tripe_Math::cross(Right, Front));

	viewMatrix = glm::lookAt(transform.translate.GetBaseVector(), (transform.translate + Front).GetBaseVector(), Up.GetBaseVector());
}

void Camera::calculate_Projection() {
	if (camType == Camera_Type::ORTHOGRAPHIC) {
		//Change later
		projectionMatrix = glm::perspective(glm::radians(zoom), aspectRatio, near, far);
	}
	else if (camType == Camera_Type::PERSPECTIVE) {
		projectionMatrix = glm::perspective(glm::radians(zoom), aspectRatio, near, far);
	}
}

glm::mat4 Camera::View_Projection_Matrix() {

	return projectionMatrix * viewMatrix;
}