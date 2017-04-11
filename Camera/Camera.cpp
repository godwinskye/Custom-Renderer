#include "Camera.h"

Camera::~Camera() {
	delete Space;
}

void Camera::SetFrustum(ViewFrustum view) {
	Frustum = view;
}

void Camera::SetSpace(Matrix * mat) {
	Space = mat;
}
