#include "PolyFill.h"
#include "LineRender.h"

#define ALTER

void PolyFill::Triangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color) {
	int currentIter;
	//PolyFill::LongestTriLine package1 = DetermineLongest(origin, endpoint1, endpoint2);

	LineRenderer::FillPack line11 = LineRenderer::PolyDDArender(drawable, origin, endpoint1, color);
	LineRenderer::FillPack line22 = LineRenderer::PolyDDArender(drawable, origin, endpoint2, color);
	LineRenderer::FillPack line33 = LineRenderer::PolyDDArender(drawable, endpoint1, endpoint2, color);
	PolyFill::LongestTriLine package = LineRenderer::FindLongest(line11, line22, line33);

	LineRenderer::FillPack longestline = LineRenderer::PolyDDArender(drawable, package.longest.origin, package.longest.endpoint, color);
	LineRenderer::FillPack line2 = LineRenderer::PolyDDArender(drawable, package.shorter1.origin, package.shorter1.endpoint, color);
	LineRenderer::FillPack line3 = LineRenderer::PolyDDArender(drawable, package.shorter2.origin, package.shorter2.endpoint, color);
	int something;

	if (longestline.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
			}
		}
		
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
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
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}
		
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}
		
	}
}



//For blend use in page 5 only
void PolyFill::BTriangle(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color) {
	int currentIter;
	//PolyFill::LongestTriLine package1 = DetermineLongest(origin, endpoint1, endpoint2);

	LineRenderer::FillPack line11 = LineRenderer::PolyDDArender(drawable, origin, endpoint1, color);
	LineRenderer::FillPack line22 = LineRenderer::PolyDDArender(drawable, origin, endpoint2, color);
	LineRenderer::FillPack line33 = LineRenderer::PolyDDArender(drawable, endpoint1, endpoint2, color);
	PolyFill::LongestTriLine package = LineRenderer::FindLongest(line11, line22, line33);

	LineRenderer::FillPack longestline = LineRenderer::PolyDDArender(drawable, package.longest.origin, package.longest.endpoint, color);
	LineRenderer::FillPack line2 = LineRenderer::PolyDDArender(drawable, package.shorter1.origin, package.shorter1.endpoint, color);
	LineRenderer::FillPack line3 = LineRenderer::PolyDDArender(drawable, package.shorter2.origin, package.shorter2.endpoint, color);
	int something;

	//Setting new blend with white

	const double opacity = 0.14;
	unsigned int chosenColor = 0xffffffff;   //white
	unsigned int oldColor = color;
	unsigned int newColor = opacity * chosenColor + (1 - opacity) * oldColor;
	color = newColor;

	if (longestline.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], color);
				}
			}
		}

		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], currentIter, longestline.map[currentIter], color);
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
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
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
				else {
					currentIter = package.shorter1.origin.x - i;
					if (longestline.map.find(line2.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line2.map[currentIter], longestline.map[line2.map[currentIter]], line2.map[currentIter], color);
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = package.shorter1.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter1.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line2.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}

		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.x + i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
				else {
					currentIter = package.shorter2.origin.x - i;
					if (longestline.map.find(line3.map[currentIter]) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, currentIter, line3.map[currentIter], longestline.map[line3.map[currentIter]], line3.map[currentIter], color);
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = package.shorter2.origin.y + i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
				else {
					currentIter = package.shorter2.origin.y - i;
					if (longestline.map.find(currentIter) == longestline.map.end()) {
						continue;
					}
					LineRenderer::DDArender(drawable, line3.map[currentIter], currentIter, longestline.map[currentIter], currentIter, color);
				}
			}
		}

	}
}

void PolyFill::TriFill(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color) {
	std::vector<SLP> Chains = GetChain(origin, endpoint1, endpoint2);
	bool finished = false;

	SLP currentpair1 = Chains[0];
	double gradient1 = MathWiz::GetGradientS(currentpair1.point1, currentpair1.point2);
	OctantWiz::SPoint diffpoint1(currentpair1.point2.x - currentpair1.point1.x, currentpair1.point2.y - currentpair1.point1.y);
	OctantWiz::Octant pair1octant = OctantWiz::FindOctantS(diffpoint1);

	SLP currentpair2 = Chains[1];
	double gradient2 = MathWiz::GetGradientS(currentpair2.point1, currentpair2.point2);
	OctantWiz::SPoint diffpoint2(currentpair2.point2.x - currentpair2.point1.x, currentpair2.point2.y - currentpair2.point1.y);
	OctantWiz::Octant pair2octant = OctantWiz::FindOctantS(diffpoint2);

	while (!finished) {
		currentpair1 = GetNextPointWhileDDA(drawable, currentpair1, gradient1, pair1octant);
		currentpair2 = RecordGetNextPointWhileDDA(drawable, currentpair2, gradient2, pair2octant, ALTER finished);
		LineRenderer::DDArender(drawable, currentpair1.point1.x, currentpair1.point1.y, 
								currentpair2.point1.x, currentpair2.point1.y, color);
	}

	currentpair2 = Chains[2];
	finished = false;
	double gradient3 = MathWiz::GetGradientS(currentpair2.point1, currentpair2.point2);
	OctantWiz::SPoint diffpoint3(currentpair2.point2.x - currentpair2.point1.x, currentpair2.point2.y - currentpair2.point1.y);
	OctantWiz::Octant pair3octant = OctantWiz::FindOctantS(diffpoint3);

	while (!finished) {
		currentpair1 = GetNextPointWhileDDA(drawable, currentpair1, gradient1, pair1octant);
		currentpair2 = RecordGetNextPointWhileDDA(drawable, currentpair2, gradient3, pair3octant, ALTER finished);
		LineRenderer::DDArender(drawable, currentpair1.point1.x, currentpair1.point1.y,
								currentpair2.point1.x, currentpair2.point1.y, color);
	}
}

//Returns static chain as element [0] and dynamic chain at elements [1] and [2]
std::vector<PolyFill::SLP> PolyFill::GetChain(OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2) {
	return std::vector<PolyFill::SLP>();
}

PolyFill::SLP PolyFill::GetNextPointWhileDDA(Drawable *drawable, SLP currentpair, double gradient, OctantWiz::Octant pairOctant) {
	return SLP();
}

PolyFill::SLP PolyFill::RecordGetNextPointWhileDDA(Drawable *drawable, SLP currentpair, double gradient, OctantWiz::Octant pairOctant, bool & finished) {
	return SLP();
}
