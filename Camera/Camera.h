#pragma once
#include "ViewFrustum.h"
#include "Matrix\Matrix.h"

struct Camera {
	ViewFrustum Frustum;
	Matrix* Space = new Matrix(4, 4, MType::ZERO);

	Camera() {}

	Camera(ViewFrustum view, Matrix* mat) {
		Frustum = view;
		Space = mat;
	}

	~Camera();

	void SetFrustum(ViewFrustum view);
	void SetSpace(Matrix* mat);
};