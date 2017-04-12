#pragma once
#include "ViewFrustum.h"
#include "Matrix\Matrix.h"

struct Camera {
	ViewFrustum Frustum;
	ViewFrustum Original;
	Matrix* Space = new Matrix(4, 4, MType::ZERO);

	Camera() {}

	Camera(ViewFrustum view, ViewFrustum orig, Matrix* mat) {
		Frustum = view;
		Original = orig;
		Space = mat;
	}

	~Camera();

	void SetFrustum(ViewFrustum view);
	void SetOriginal(ViewFrustum view);
	void SetSpace(Matrix* mat);
};