#include "PolyFill.h"
#include "LineRender.h"

#define ALTER

void PolyFill::Triangle(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color) {
	std::vector<OctantWiz::Point> list;
	OctantWiz::Point top, middle, bottom;
	list.push_back(origin);
	list.push_back(endpoint1);
	list.push_back(endpoint2);
	bool leftIsVar = false;

	bottom = MathWiz::GetLargestYAndRemoveIt(list);
	middle = MathWiz::GetLargestYAndRemoveIt(list);
	top = MathWiz::GetLargestYAndRemoveIt(list);

	if (top.y == middle.y && top.x < bottom.x) {
		OctantWiz::Point temp = top;
		top = middle;
		middle = temp;
	}

	double gradient = MathWiz::GetReverseGradient(top, middle);
	double fgradient = MathWiz::GetReverseGradient(top, bottom);

	double leftpoint, rightpoint;
	double lgradient, rgradient;

	if (middle.x <= bottom.x) {
		leftpoint = top.x + gradient;
		rightpoint = top.x + fgradient;
		lgradient = gradient;
		rgradient = fgradient;
		if (top.x == middle.x) {
			lgradient = 0;
		}
		else if (top.x == bottom.x) {
			rgradient = 0;
		}
		leftIsVar = true;
	}
	else {
		leftpoint = top.x + fgradient;
		rightpoint = top.x + gradient;
		lgradient = fgradient;
		rgradient = gradient;
		if (top.x == middle.x) {
			rgradient = 0;
		}
		else if (top.x == bottom.x) {
			lgradient = 0;
		}
		leftIsVar = false;
	}

	
	for (int y = top.y + 1; y < middle.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			drawable->setPixel(x, y, color);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;
	}



	if (leftIsVar) {
		lgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			lgradient = 0;
		}
		if (leftpoint > middle.x) {
			leftpoint = middle.x;
		}
	}
	else {
		rgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			rgradient = 0;
		}
		rightpoint = middle.x;
	}




	for (int y = middle.y; y < bottom.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			drawable->setPixel(x, y, color);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;
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

/**********************************************************************************************************/
/**************************************UNUSED SEGMENT******************************************************/
/**********************************************************************************************************/
void PolyFill::TriFill(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color) {
	std::vector<SLP> Chains = GetChain(origin, endpoint1, endpoint2);
	bool finished = false;

	LineRenderer::DDArender(drawable, origin.x, origin.y, endpoint1.x, endpoint1.y, color);
	LineRenderer::DDArender(drawable, origin.x, origin.y, endpoint2.x, endpoint2.y, color);
	LineRenderer::DDArender(drawable, endpoint1.x, endpoint1.y, endpoint2.x, endpoint2.y, color);

	SLP currentpair1 = Chains[0];
	double gradient1 = MathWiz::GetGradientS(currentpair1.point1, currentpair1.point2);
	OctantWiz::SPoint diffpoint1(currentpair1.point2.x - currentpair1.point1.x, currentpair1.point2.y - currentpair1.point1.y);
	OctantWiz::Octant pair1octant = OctantWiz::FindOctantS(diffpoint1);

	SLP currentpair2 = Chains[1];
	double gradient2 = MathWiz::GetGradientS(currentpair2.point1, currentpair2.point2);
	OctantWiz::SPoint diffpoint2(currentpair2.point2.x - currentpair2.point1.x, currentpair2.point2.y - currentpair2.point1.y);
	OctantWiz::Octant pair2octant = OctantWiz::FindOctantS(diffpoint2);

	while (!finished) {
		currentpair1 = RecordGetNextPointWhileDDA(drawable, currentpair1, gradient1, pair1octant, color, ALTER finished);
		currentpair2 = RecordGetNextPointWhileDDA(drawable, currentpair2, gradient2, pair2octant, color, ALTER finished);
		LineRenderer::DDArender(drawable, currentpair1.point1.x, currentpair1.point1.y, 
								currentpair2.point1.x, currentpair2.point1.y, color);
	}

	currentpair2 = Chains[2];
	finished = false;
	double gradient3 = MathWiz::GetGradientS(currentpair2.point1, currentpair2.point2);
	OctantWiz::SPoint diffpoint3(currentpair2.point2.x - currentpair2.point1.x, currentpair2.point2.y - currentpair2.point1.y);
	OctantWiz::Octant pair3octant = OctantWiz::FindOctantS(diffpoint3);

	while (!finished) {
		currentpair1 = RecordGetNextPointWhileDDA(drawable, currentpair1, gradient1, pair1octant, color, ALTER finished);
		currentpair2 = RecordGetNextPointWhileDDA(drawable, currentpair2, gradient3, pair3octant, color, ALTER finished);
		LineRenderer::DDArender(drawable, currentpair1.point1.x, currentpair1.point1.y,
								currentpair2.point1.x, currentpair2.point1.y, color);
	}
}

//Returns static chain as element [0] and dynamic chain at elements [1] and [2]
std::vector<PolyFill::SLP> PolyFill::GetChain(OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2) {
	std::vector<PolyFill::SLP> Chains;

	PolyFill::SLP pair1(origin, endpoint1);
	PolyFill::SLP pair2(origin, endpoint2);
	PolyFill::SLP pair3(endpoint2, endpoint1);

	double length1 = MathWiz::FindLongestLength(pair1.point1, pair1.point2);
	double length2 = MathWiz::FindLongestLength(pair2.point1, pair2.point2);
	double length3 = MathWiz::FindLongestLength(pair3.point1, pair3.point2);

	if (length1 >= length2 && length1 >= length3) {
		Chains.push_back(pair1);
		Chains.push_back(pair2);
		Chains.push_back(pair3);
		return Chains;
	}
	else if (length2 >= length1 && length2 >= length3) {
		Chains.push_back(pair2);
		Chains.push_back(pair1);
		PolyFill::SLP rearrangepair(endpoint1, endpoint2);
		Chains.push_back(rearrangepair);
		return Chains;
	}
	else {
		Chains.push_back(pair3);
		PolyFill::SLP rearrangepair1(endpoint2, origin);
		PolyFill::SLP rearrangepair2(origin, endpoint1);
		Chains.push_back(rearrangepair1);
		Chains.push_back(rearrangepair2);
		return Chains;
	}
}

PolyFill::SLP PolyFill::GetNextPointWhileDDA(Drawable *drawable, SLP currentpair, double gradient, OctantWiz::Octant pairOctant, unsigned int color) {
	switch (pairOctant) {						//ugly octant switch

	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		drawable->setPixel(currentpair.point1.x, round(currentpair.point1.y), color);
		currentpair.point1.x += 1;
		currentpair.point1.y += gradient;
		break;

	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		drawable->setPixel(round(currentpair.point1.x), currentpair.point1.y, color);
		currentpair.point1.x -= 1 / gradient;
		currentpair.point1.y -= 1;
		break;

	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		drawable->setPixel(currentpair.point1.x, round(currentpair.point1.y), color);
		currentpair.point1.x -= 1;
		currentpair.point1.y -= gradient;
		break;

	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		drawable->setPixel(round(currentpair.point1.x), currentpair.point1.y, color);
		currentpair.point1.x += 1 / gradient;
		currentpair.point1.y += 1;
		break;

	}

	return currentpair;
}

PolyFill::SLP PolyFill::RecordGetNextPointWhileDDA(Drawable *drawable, SLP currentpair, double gradient, OctantWiz::Octant pairOctant, unsigned int color, bool & finished) {
	switch (pairOctant) {						//ugly octant switch

	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		drawable->setPixel(currentpair.point1.x, round(currentpair.point1.y), color);
		currentpair.point1.x += 1;
		currentpair.point1.y += gradient;
		if (currentpair.point1.x == currentpair.point2.x) {
			finished = true;
		}
		break;

	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		drawable->setPixel(round(currentpair.point1.x), currentpair.point1.y, color);
		currentpair.point1.x -= 1 / gradient;
		currentpair.point1.y -= 1;
		if (currentpair.point1.y == currentpair.point2.y) {
			finished = true;
		}
		break;

	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		drawable->setPixel(currentpair.point1.x, round(currentpair.point1.y), color);
		currentpair.point1.x -= 1;
		currentpair.point1.y -= gradient;
		if (currentpair.point1.x == currentpair.point2.x) {
			finished = true;
		}
		break;

	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		drawable->setPixel(round(currentpair.point1.x), currentpair.point1.y, color);
		currentpair.point1.x += 1 / gradient;
		currentpair.point1.y += 1;
		if (currentpair.point1.y == currentpair.point2.y) {
			finished = true;
		}
		break;

	}

	return currentpair;
}
