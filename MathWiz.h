#pragma once
#include "OctantWiz.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

namespace MathWiz {

	enum class Quadrant {
		Quadrant1,
		Quadrant2,
		Quadrant3,
		Quadrant4
	};

	double GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint);
	OctantWiz::Point DetermineEndPoint(double currentangle, int length, int x, int y);
	Quadrant DetermineQuadrant(double angle);

	// AArender() functions
	void swap(int &first, int &second);
	double fpart(double number);
	double rfpart(double number);
	unsigned int alphatoblackvar(double alphafloat);
}