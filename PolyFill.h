#pragma once
#include "OctantWiz.h"
#include "MathWiz.h"
#include "LineRender.h"
#include "renderarea361.h"

namespace PolyFill {

	struct LinePair {
		OctantWiz::Point origin;
		OctantWiz::Point endpoint;

		LinePair() {}
		LinePair(OctantWiz::Point first, OctantWiz::Point second) {
			origin = first;
			endpoint = second;
		}
	};

	struct LongestTriLine {
		LinePair longest;
		LinePair shorter1;
		LinePair shorter2;

		LongestTriLine() {}
		LongestTriLine(LinePair important, LinePair other1, LinePair other2) {
			longest = important;
			shorter1 = other1;
			shorter2 = other2;
		}
	};

	void Triangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2);
	LongestTriLine DetermineLongest(OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2);
}