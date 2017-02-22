#pragma once
#define _USE_MATH_DEFINES
#include "../OctantWiz/OctantWiz.h"
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
	double GetGradientS(OctantWiz::SPoint point1, OctantWiz::SPoint point2);
	OctantWiz::Point DetermineEndPoint(double currentangle, int length, int x, int y);
	Quadrant DetermineQuadrant(double angle);
	unsigned int RandomCoordinate(unsigned int lower, unsigned int upper);
	unsigned int RandomRGBHex();
	double PointDistance(OctantWiz::Point origin, OctantWiz::Point endpoint);
	double LargestOfThree(double first, double second, double third);
	double FindLongestLength(OctantWiz::SPoint origin, OctantWiz::SPoint endpoint);
}