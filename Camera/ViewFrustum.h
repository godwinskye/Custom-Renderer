#pragma once

struct ViewFrustum {
	double xlow;
	double ylow;
	double xhigh;
	double yhigh;
	double hither;
	double yon;

	ViewFrustum() {
		xlow = 0, ylow = 0, xhigh = 0, yhigh = 0, hither = 0, yon = 0;
	}

	ViewFrustum(double first, double second, double third, double fourth, double fifth, double sixth) {
		xlow = first, ylow = second, xhigh = third, yhigh = fourth, hither = fifth, yon = sixth;
	}
};