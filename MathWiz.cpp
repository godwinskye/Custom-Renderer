#include "MathWiz.h"

//to only calculate this once
double thirdquad = 1.5 * M_PI;

double MathWiz::GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	return (double)(endpoint.y - origin.y) / (double)(endpoint.x - origin.x);
}

OctantWiz::Point MathWiz::DetermineEndPoint(double currentangle, int length, int x, int y) {
	int x_diff = length * cos(currentangle);
	int y_diff = length * sin(currentangle);
	MathWiz::Quadrant quadrant = DetermineQuadrant(currentangle);
	
	switch (quadrant) {
	case MathWiz::Quadrant::Quadrant1:
		//logic code
		break;
	case MathWiz::Quadrant::Quadrant2:
		//logic code
		break;
	case MathWiz::Quadrant::Quadrant3:
		//logic code
		break;
	case MathWiz::Quadrant::Quadrant4:
		//logic code
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
