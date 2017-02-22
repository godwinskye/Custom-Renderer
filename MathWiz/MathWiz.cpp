#include "MathWiz.h"
#include <stdlib.h>

//to only calculate this once
static double thirdquad = M_PI + M_PI_2;

double MathWiz::GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	return (double)(endpoint.y - origin.y) / (double)(endpoint.x - origin.x);
}

double MathWiz::GetGradientS(OctantWiz::SPoint point1, OctantWiz::SPoint point2) {
	return (point2.y - point1.y) / (point2.x - point1.x);
}

OctantWiz::Point MathWiz::DetermineEndPoint(double currentangle, int length, int x, int y) {
	MathWiz::Quadrant quadrant = DetermineQuadrant(currentangle);
	
	switch (quadrant) {
	case MathWiz::Quadrant::Quadrant1: {
		int x_diff = length * cos(currentangle);
		int y_diff = length * sin(currentangle);
		OctantWiz::Point endpoint(x + x_diff, y - y_diff);
		return endpoint;
	}
		break;
	case MathWiz::Quadrant::Quadrant2: {
		int x_diff = length * cos(M_PI - currentangle);
		int y_diff = length * sin(M_PI - currentangle);
		OctantWiz::Point endpoint(x - x_diff, y - y_diff);
		return endpoint;
	}
		break;
	case MathWiz::Quadrant::Quadrant3: {
		int x_diff = length * sin(thirdquad - currentangle);
		int y_diff = length * cos(thirdquad - currentangle);
		OctantWiz::Point endpoint(x - x_diff, y + y_diff);
		return endpoint;
	}
		break;
	case MathWiz::Quadrant::Quadrant4: {
		int x_diff = length * cos(2 * M_PI - currentangle);
		int y_diff = length * sin(2 * M_PI - currentangle);
		OctantWiz::Point endpoint(x + x_diff, y + y_diff);
		return endpoint;
	}
		break;
	}
}

MathWiz::Quadrant MathWiz::DetermineQuadrant(double angle) {
	if (angle <= M_PI_2) {
		return MathWiz::Quadrant::Quadrant1;
	}
	else if (angle > M_PI_2 && angle <= M_PI) {
		return MathWiz::Quadrant::Quadrant2;
	}
	else if (angle > M_PI && angle <= thirdquad) {
		return MathWiz::Quadrant::Quadrant3;
	}
	else {
		return MathWiz::Quadrant::Quadrant4;
	}
}

unsigned int MathWiz::RandomCoordinate(unsigned int lower, unsigned int upper) {
	unsigned int coordinate = rand() % upper + lower;
	return coordinate;
}

unsigned int MathWiz::RandomRGBHex() {
	unsigned int range = 256;
	unsigned int red = rand() % range;
	unsigned int green = rand() % range;
	unsigned int blue = rand() % range;

	unsigned int colour = (0xff << 24) + ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	return colour;
}

double MathWiz::PointDistance(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	double xpart = pow(endpoint.x - origin.x, 2);
	double ypart = pow(endpoint.y - origin.y, 2);
	double distance = sqrt(xpart + ypart);
	return distance;
}

double MathWiz::LargestOfThree(double first, double second, double third) {
	if (first >= second && first >= third) {
		return first;
	}
	else if (second >= first && second >= third) {
		return second;
	}
	else {
		return third;
	}
}

double MathWiz::FindLongestLength(OctantWiz::SPoint origin, OctantWiz::SPoint endpoint) {
	double length1 = abs(endpoint.x - origin.x);
	double length2 = abs(endpoint.y - origin.y);

	if (length1 >= length2) {
		return length1;
	}
	else {
		return length2;
	}
}


