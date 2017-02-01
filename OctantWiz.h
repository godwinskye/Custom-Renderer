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

	Octant FindOctant(Point endpoint);
}