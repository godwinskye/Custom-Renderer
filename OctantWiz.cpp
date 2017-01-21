#include "OctantWiz.h"

/*************************************************************************************************************
DOCUMENTATION:
Pixels going downward are in the positive direction (reverse-y), so the octants are reflected onto the x-axis
*************************************************************************************************************/

OctantWiz::Octant OctantWiz::FindOctant(Point diffpoint) {
	if (diffpoint.x > 0) {
		if (diffpoint.y > 0) {
			if (abs(diffpoint.x) >= abs(diffpoint.y)) {
				return Octant::OctantEight;
			}
			else {
				return Octant::OctantSeven;
			}
		}
		else {
			if (abs(diffpoint.x) >= abs(diffpoint.y)) {
				return Octant::OctantOne;
			}
			else {
				return Octant::OctantTwo;
			}
		}
	}
	else {
		if (diffpoint.y > 0) {
			if (abs(diffpoint.x) >= abs(diffpoint.y)) {
				return Octant::OctantFive;
			}
			else {
				return Octant::OctantSix;
			}
		}
		else {
			if (abs(diffpoint.x) >= abs(diffpoint.y)) {
				return Octant::OctantFour;
			}
			else {
				return Octant::OctantThree;
			}
		}
	}
}
