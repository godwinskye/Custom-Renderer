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

	for (int i = 0; i < longestline.map.size(); i++) {
		if (longestline.xiter) {
			if (longestline.movepositive) {
				currentIter = package.longest.origin.x + i;
				int somepoint = line2.map[currentIter];      //TODO figure out why value is not being assigned right
				if (line2.xiter) {
					if (line2.map.find(currentIter) != line2.map.end() && !hitend1) {       //found && in line2 && xiter == positive
						if (currentIter == package.shorter1.endpoint.x) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], currentIter, line2.map[currentIter], color);
						continue;
					}
				}
				else {
					if (line2.map.find(longestline.map[currentIter]) != line2.map.end() && !hitend1) {   //found && in line2 && !xiter
						if (longestline.map[currentIter] == package.shorter1.endpoint.y) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], line2.map[longestline.map[currentIter]], longestline.map[currentIter], color);
						continue;
					}
				}
				if (line3.xiter) {
					if (line3.map.find(currentIter) != line3.map.end() && !hitend2) {
						if (currentIter == package.shorter2.endpoint.x) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], currentIter, line3.map[currentIter], color);
						continue;
					}
				}
				else {
					if (line3.map.find(longestline.map[currentIter]) != line3.map.end() && !hitend2) {
						if (longestline.map[currentIter] == package.shorter2.endpoint.y) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], line3.map[longestline.map[currentIter]], longestline.map[currentIter], color);
						continue;
					}
				}
			}
			else {               //moveneg
				currentIter = package.longest.origin.x - i;
				if (line2.xiter) {
					if (line2.map.find(currentIter) != line2.map.end() && !hitend1) {       //found && in line2 && xiter == positive
						if (currentIter == package.shorter1.endpoint.x) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], currentIter, line2.map[currentIter], color);
						continue;
					}
				}
				else {
					if (line2.map.find(longestline.map[currentIter]) != line2.map.end() && !hitend1) {   //found && in line2 && !xiter
						if (longestline.map[currentIter] == package.shorter1.endpoint.y) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], line2.map[longestline.map[currentIter]], longestline.map[currentIter], color);
						continue;
					}
				}
				if (line3.xiter) {
					if (line3.map.find(currentIter) != line3.map.end() && !hitend2) {
						if (currentIter == package.shorter2.endpoint.x) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], currentIter, line3.map[currentIter], color);
						continue;
					}
				}
				else {
					if (line3.map.find(longestline.map[currentIter]) != line3.map.end() && !hitend2) {
						if (longestline.map[currentIter] == package.shorter2.endpoint.y) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, currentIter, longestline.map[currentIter], line3.map[longestline.map[currentIter]], longestline.map[currentIter], color);
						continue;
					}
				}
			}
		}
		else {              //longestline.xiter == neg    key = y-value
			if (longestline.movepositive) {
				currentIter = package.longest.origin.y + i;
				if (line2.xiter) {
					if (line2.map.find(longestline.map[currentIter]) != line2.map.end() && !hitend1) {
						if (longestline.map[currentIter] == package.shorter1.endpoint.x) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, longestline.map[currentIter], line2.map[longestline.map[currentIter]], color);
						continue;
					}
				}
				else {
					if (line2.map.find(currentIter) != line2.map.end() && !hitend1) {
						if (currentIter == package.shorter1.endpoint.y) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, line2.map[currentIter], currentIter, color);
						continue;
					}
				}
				if (line3.xiter) {
					if (line3.map.find(longestline.map[currentIter]) != line3.map.end() && !hitend2) {
						if (longestline.map[currentIter] == package.shorter2.endpoint.x) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, longestline.map[currentIter], line3.map[longestline.map[currentIter]], color);
						continue;
					}
				}
				else {
					if (line3.map.find(currentIter) != line3.map.end() && !hitend2) {
						if (currentIter == package.shorter2.endpoint.y) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, line3.map[currentIter], currentIter, color);
						continue;
					}
				}
			}
			else {      //moveneg
				currentIter = package.longest.origin.y - i;
				if (line2.xiter) {
					if (line2.map.find(longestline.map[currentIter]) != line2.map.end() && !hitend1) {
						if (longestline.map[currentIter] == package.shorter1.endpoint.x) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, longestline.map[currentIter], line2.map[longestline.map[currentIter]], color);
						continue;
					}
				}
				else {
					if (line2.map.find(currentIter) != line2.map.end() && !hitend1) {
						if (currentIter == package.shorter1.endpoint.y) {
							hitend1 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, line2.map[currentIter], currentIter, color);
						continue;
					}
				}
				if (line3.xiter) {
					if (line3.map.find(longestline.map[currentIter]) != line3.map.end() && !hitend2) {
						if (longestline.map[currentIter] == package.shorter2.endpoint.x) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, longestline.map[currentIter], line3.map[longestline.map[currentIter]], color);
						continue;
					}
				}
				else {
					if (line3.map.find(currentIter) != line3.map.end() && !hitend2) {
						if (currentIter == package.shorter2.endpoint.y) {
							hitend2 = true;
						}
						LineRenderer::DDArender(drawable, longestline.map[currentIter], currentIter, line3.map[currentIter], currentIter, color);
						continue;
					}
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
