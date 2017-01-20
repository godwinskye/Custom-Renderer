#pragma once

namespace OctantWiz {

	struct Point {
		int x;
		int y;

		Point(int a, int b) {
			x = a;
			y = b;
		}
	};


	void SetPixelByOctant(Point origin, Point endpoint);
}