#include "OctantWiz.h"

OctantWiz::Octant OctantWiz::FindOctant(Point endpoint) {
	if (endpoint.x > 0) {
		if (endpoint.y > 0) {
			if (abs(endpoint.x) >= abs(endpoint.y)) {
				return Octant::OctantOne;
			}
			else {
				return Octant::OctantTwo;
			}
		}
		else {
			if (abs(endpoint.x) >= abs(endpoint.y)) {
				return Octant::OctantEight;
			}
			else {
				return Octant::OctantSeven;
			}
		}
	}
	else {
		if (endpoint.y > 0) {
			if (abs(endpoint.x) >= abs(endpoint.y)) {
				return Octant::OctantFour;
			}
			else {
				return Octant::OctantThree;
			}
		}
		else {
			if (abs(endpoint.x) >= abs(endpoint.y)) {
				return Octant::OctantFive;
			}
			else {
				return Octant::OctantSix;
			}
		}
	}
}
