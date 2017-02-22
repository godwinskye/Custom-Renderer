#pragma once
#include <cmath>

namespace OctantWiz {

	struct Point {
		int x;
		int y;

		Point() {
			x = 0;
			y = 0;
		}

		Point(int a, int b) {
			x = a;
			y = b;
		}
	};

	struct SPoint {
		double x;
		double y;

		SPoint() {
			x = 0.f;
			y = 0.f;
		}

		SPoint(double a, double b) {
			x = a;
			y = b;
		}

		SPoint(Point point) {
			x = static_cast<double>(point.x);
			y = static_cast<double>(point.y);
		}
	};

	enum class Octant {
		OctantOne,
		OctantTwo,
		OctantThree,
		OctantFour,
		OctantFive,
		OctantSix,
		OctantSeven,
		OctantEight
	};

	Octant FindOctant(Point diffpoint);
	Octant FindOctantS(SPoint diffpoint);
}