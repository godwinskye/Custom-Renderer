#include "MathWiz.h"

//to only calculate this once
double thirdquad = M_PI + M_PI_2;

double MathWiz::GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	return (double)(endpoint.y - origin.y) / (double)(endpoint.x - origin.x);
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
