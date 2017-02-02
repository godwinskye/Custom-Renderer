#include "PolyFill.h"

void PolyFill::Triangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2) {
	unsigned int color = 0xff000000;
	int currentIter;
	PolyFill::LongestTriLine package = DetermineLongest(origin, endpoint1, endpoint2);
	LineRenderer::FillPack longestline = LineRenderer::PolyDDArender(drawable, package.longest.origin, package.longest.endpoint, color);
	LineRenderer::FillPack line2 = LineRenderer::PolyDDArender(drawable, package.shorter1.origin, package.shorter1.endpoint, color);
	LineRenderer::FillPack line3 = LineRenderer::PolyDDArender(drawable, package.shorter2.origin, package.shorter2.endpoint, color);
	bool hitend1 = false;
	bool hitend2 = false;

	if (longestline.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
			}
		}
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], color);
				}
			}
		}
	}
	else {    //longestline is a yiter
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}
	}
}

PolyFill::LongestTriLine PolyFill::DetermineLongest(OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2) {
	double dist1 = MathWiz::PointDistance(origin, endpoint1);
	double dist2 = MathWiz::PointDistance(origin, endpoint2);
	double dist3 = MathWiz::PointDistance(endpoint1, endpoint2);

	LinePair pair1 = LinePair(origin, endpoint1);
	LinePair pair2 = LinePair(origin, endpoint2);
	LinePair pair3 = LinePair(endpoint1, endpoint2);

	double largest = MathWiz::LargestOfThree(dist1, dist2, dist3);

	if (largest == dist1) {
		return LongestTriLine(pair1, pair2, pair3);
	}
	else if (largest == dist2) {
		return LongestTriLine(pair2, pair1, pair3);
	}
	else {
		return LongestTriLine(pair3, pair1, pair2);
	}
}
