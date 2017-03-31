#pragma once
#include "../OctantWiz/OctantWiz.h"
#include "../MathWiz/MathWiz.h"
#include "renderarea361.h"

namespace PolyFill {

	void Hooker(OctantWiz::Point, OctantWiz::Point, OctantWiz::Point);

	struct LinePair {
		OctantWiz::Point origin;
		OctantWiz::Point endpoint;

		LinePair() {}
		LinePair(OctantWiz::Point originpoint, OctantWiz::Point endingpoint) {
			origin = originpoint;
			endpoint = endingpoint;
		}
	};

	struct LinePair3D {
		OctantWiz::Point3D origin;
		OctantWiz::Point3D endpoint;

		LinePair3D() {}
		LinePair3D(OctantWiz::Point3D originpoint, OctantWiz::Point3D endingpoint) {
			origin = originpoint;
			endpoint = endingpoint;
		}
	};

	struct SLP {					//special LinePair
		OctantWiz::SPoint point1;
		OctantWiz::SPoint point2;

		SLP() {}

		SLP(OctantWiz::SPoint firstpoint, OctantWiz::SPoint secondpoint) {
			point1 = firstpoint;
			point2 = secondpoint;
		}

		SLP(OctantWiz::Point origin, OctantWiz::Point endpoint) {
			point1 = origin;
			point2 = endpoint;
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

	struct LongestTriLine3D {
		LinePair3D longest;
		LinePair3D shorter1;
		LinePair3D shorter2;

		LongestTriLine3D() {}
		LongestTriLine3D(LinePair3D important, LinePair3D other1, LinePair3D other2) {
			longest = important;
			shorter1 = other1;
			shorter2 = other2;
		}
	};

	void Triangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color);
	void BTriangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color);

	//Refactored implementation
	//Unused as of now - still under development
	void TriFill(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color);
	std::vector<SLP> GetChain(OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2);
	SLP GetNextPointWhileDDA(Drawable *drawable, SLP currentpair, double gradient, OctantWiz::Octant pairOctant, unsigned int color);
	SLP RecordGetNextPointWhileDDA(Drawable *drawable, SLP currentpair, double gradient, OctantWiz::Octant pairOctant, unsigned int color, bool &finished);
}