#include "LineRender.h"


void LineRenderer::DDArender(Drawable *drawable,int x1, int y1, int x2, int y2, unsigned int color) {
	OctantWiz::Point origin(x1, y1);
	OctantWiz::Point endpoint(x2, y2);
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(x2 - x1, y2 - y1);

	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {							//rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		RenderOctant1Or8(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		RenderOctant2Or3(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		RenderOctant4Or5(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		RenderOctant6Or7(drawable, origin, endpoint, gradient, color);
		break;
	}
}

void LineRenderer::BRErender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color) {
	OctantWiz::Point origin(x1, y1);
	OctantWiz::Point endpoint(x2, y2);
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(x2 - x1, y2 - y1);

	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {                              //rather ugly switch
	case OctantWiz::Octant::OctantOne:
		BRenderOctant1(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantTwo:
		BRenderOctant2(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantThree:
		BRenderOctant3(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantFour:
		BRenderOctant4(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantFive:
		BRenderOctant5(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantSix:
		BRenderOctant6(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantSeven:
		BRenderOctant7(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantEight:
		BRenderOctant8(drawable, origin, endpoint, gradient, color);
		break;
	}
}

void LineRenderer::AArender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color) {
	//AArender();
}

LineRenderer::FillPack LineRenderer::PolyDDArender(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, unsigned int color) {
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(endpoint.x - origin.x, endpoint.y - origin.y);
	FillPack line;

	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {                              //rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		line = PolyRenderOctant1Or8(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		line = PolyRenderOctant2Or3(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		line = PolyRenderOctant4Or5(drawable, origin, endpoint, gradient, color);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		line = PolyRenderOctant6Or7(drawable, origin, endpoint, gradient, color);
		break;
	}
	return line;
}



/*============================================================================================*/
/*-----------------------------------IMPLEMENTATION DETAILS-----------------------------------*/
/*============================================================================================*/


void LineRenderer::RenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	double currentY = origin.y;
	for (int x = origin.x; x <= endpoint.x; x++) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY + gradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	for (int y = origin.y; y >= endpoint.y; y--) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX - reversegradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	double currentY = origin.y;
	for (int x = origin.x; x >= endpoint.x; x--) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY - gradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	for (int y = origin.y; y <= endpoint.y; y++) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX + reversegradient;
	}
	drawable->updateScreen();
}

void LineRenderer::BRenderOctant1(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int y = origin.y;
	int error = 0;
	
	for (int x = origin.x; x <= endpoint.x; x++) {
		drawable->setPixel(x, y, color);
		if ((error - dy) << 1 < dx) {
			error = error - dy;
		}
		else {
			y = y - 1;
			error = error - dy - dx;
		}
	}
}

void LineRenderer::BRenderOctant2(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int x = origin.x;
	int error = 0;

	for (int y = origin.y; y >= endpoint.y; y--) {
		drawable->setPixel(x, y, color);
		if ((error + dx) << 1 < -dy) {
			error = error + dx;
		}
		else {
			x = x + 1;
			error = error + dx + dy;
		}
	}
}

void LineRenderer::BRenderOctant3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int x = origin.x;
	int error = 0;

	for (int y = origin.y; y >= endpoint.y; y--) {
		drawable->setPixel(x, y, color);
		if ((error - dx) << 1 < -dy) {
			error = error - dx;
		}
		else {
			x = x - 1;
			error = error - dx + dy;
		}
	}
}

void LineRenderer::BRenderOctant4(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int y = origin.y;
	int error = 0;

	for (int x = origin.x; x >= endpoint.x; x--) {
		drawable->setPixel(x, y, color);
		if ((error - dy) << 1 < -dx) {
			error = error - dy;
		}
		else {
			y = y - 1;
			error = error - dy + dx;
		}
	}
}

void LineRenderer::BRenderOctant5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int y = origin.y;
	int error = 0;

	for (int x = origin.x; x >= endpoint.x; x--) {
		drawable->setPixel(x, y, color);
		if ((error + dy) << 1 < -dx) {
			error = error + dy;
		}
		else {
			y = y + 1;
			error = error + dy + dx;
		}
	}
}

void LineRenderer::BRenderOctant6(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int x = origin.x;
	int error = 0;

	for (int y = origin.y; y <= endpoint.y; y++) {
		drawable->setPixel(x, y, color);
		if ((error - dx) << 1 < dy) {
			error = error - dx;
		}
		else {
			x = x - 1;
			error = error - dx - dy;
		}
	}
}

void LineRenderer::BRenderOctant7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int x = origin.x;
	int error = 0;

	for (int y = origin.y; y <= endpoint.y; y++) {
		drawable->setPixel(x, y, color);
		if ((error + dx) << 1 < dy) {
			error = error + dx;
		}
		else {
			x = x + 1;
			error = error + dx - dy;
		}
	}
}

void LineRenderer::BRenderOctant8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	int dx = endpoint.x - origin.x;
	int dy = endpoint.y - origin.y;
	int y = origin.y;
	int error = 0;

	for (int x = origin.x; x <= endpoint.x; x++) {
		drawable->setPixel(x, y, color);
		if ((error + dy) << 1 < dx) {
			error = error + dy;
		}
		else {
			y = y + 1;
			error = error + dy - dx;
		}
	}
}

LineRenderer::FillPack LineRenderer::PolyRenderOctant1Or8(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	std::map<int, int> line1;
	bool xiter = true;
	bool movepositive = true;

	double currentY = origin.y;
	int tempY;
	for (int x = origin.x; x <= endpoint.x; x++) {
		tempY = round(currentY);
		line1.insert(std::pair<int, int>(x, tempY));
		//line1[x] = tempY;
		drawable->setPixel(x, tempY, color);
		currentY = currentY + gradient;
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack LineRenderer::PolyRenderOctant2Or3(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	std::map<int, int> line1;
	bool xiter = false;
	bool movepositive = false;

	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	int tempX;
	for (int y = origin.y; y >= endpoint.y; y--) {
		tempX = round(currentX);
		line1.insert(std::pair<int, int>(y, tempX));
		//line1[y] = tempX;
		drawable->setPixel(tempX, y, color);
		currentX = currentX - reversegradient;
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack LineRenderer::PolyRenderOctant4Or5(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	std::map<int, int> line1;
	bool xiter = true;
	bool movepositive = false;
	
	double currentY = origin.y;
	int tempY;
	for (int x = origin.x; x >= endpoint.x; x--) {
		tempY = round(currentY);
		line1.insert(std::pair<int, int>(x, tempY));
		//line1[x] = tempY;
		drawable->setPixel(x, tempY, color);
		currentY = currentY - gradient;
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack LineRenderer::PolyRenderOctant6Or7(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color) {
	std::map<int, int> line1;
	bool xiter = false;
	bool movepositive = true;
	
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	int tempX;
	for (int y = origin.y; y <= endpoint.y; y++) {
		tempX = round(currentX);
		line1.insert(std::pair<int, int>(y, tempX));
		//line1[y] = tempX;
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX + reversegradient;
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

void LineRenderer::FillBetweenLines(Drawable *drawable, std::vector<OctantWiz::Point> line1, std::vector<OctantWiz::Point> line2, unsigned int color) {
	int points1 = line1.size();
	int points2 = line2.size();
	int numberofpoints;

	if (points1 >= points2) {
		numberofpoints = points1;
	}
	else {
		numberofpoints = points2;
	}

	for (int i = 0; i < numberofpoints; i++) {
		DDArender(drawable, line1[i].x, line1[i].y, line2[i].x, line2[i].y, color);
	}
}

PolyFill::LongestTriLine LineRenderer::FindLongest(LineRenderer::FillPack line1, LineRenderer::FillPack line2, LineRenderer::FillPack line3) {
	PolyFill::LinePair pair1 = PolyFill::LinePair(line1.origin, line1.endpoint);
	PolyFill::LinePair pair2 = PolyFill::LinePair(line2.origin, line2.endpoint);
	PolyFill::LinePair pair3 = PolyFill::LinePair(line3.origin, line3.endpoint);

	bool trial1 = TestForLongest(line1, line2, line3);
	bool trial2 = TestForLongest(line2, line1, line3);
	bool trial3 = TestForLongest(line3, line1, line2);

	if (trial1) {
		return PolyFill::LongestTriLine(pair1, pair2, pair3);
	}
	else if (trial2) {
		return PolyFill::LongestTriLine(pair2, pair1, pair3);
	}
	else {
		return PolyFill::LongestTriLine(pair3, pair1, pair2);
	}
}

bool LineRenderer::TestForLongest(LineRenderer::FillPack line1, LineRenderer::FillPack line2, LineRenderer::FillPack line3) {
	bool flag = true;
	int currentIter;

	if (line1.xiter) {
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = line2.origin.x + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.x - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {     //line2 = yiter
				if (line2.movepositive) {
					currentIter = line2.origin.y + i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.y - i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = line3.origin.x + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.x - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {       //line3 = yiter
				if (line3.movepositive) {
					currentIter = line3.origin.y + i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.y - i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}

	}
	else {    //longestline is a yiter
		for (int i = 0; i < line2.map.size(); i++) {
			if (line2.xiter) {
				if (line2.movepositive) {
					currentIter = line2.origin.x + i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.x - i;
					if (line1.map.find(line2.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {     //line2 is a yiter
				if (line2.movepositive) {
					currentIter = line2.origin.y + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line2.origin.y - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}
		for (int i = 0; i < line3.map.size(); i++) {
			if (line3.xiter) {
				if (line3.movepositive) {
					currentIter = line3.origin.x + i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.x - i;
					if (line1.map.find(line3.map[currentIter]) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
			else {      //line3 is a yiter
				if (line3.movepositive) {
					currentIter = line3.origin.y + i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
				else {
					currentIter = line3.origin.y - i;
					if (line1.map.find(currentIter) == line1.map.end()) {
						flag = false;
						return flag;
					}
				}
			}
		}
	}
	return flag;
}