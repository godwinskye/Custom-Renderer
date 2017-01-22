#include "LineRender.h"

void LineRenderer::DDArender(Drawable *drawable,int x1, int y1, int x2, int y2) {
	OctantWiz::Point origin(x1, y1);
	OctantWiz::Point endpoint(x2, y2);
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(x2 - x1, y2 - y1);

	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {                              //rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		RenderOctant1Or8(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		RenderOctant2Or3(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		RenderOctant4Or5(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		RenderOctant6Or7(drawable, origin, endpoint, gradient);
		break;
	}
}

void LineRenderer::RenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	unsigned int color = 0xff000000;      //Black color
	double currentY = origin.y;
	for (int x = origin.x; x < endpoint.x; x++) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY + gradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	unsigned int color = 0xff000000;
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	for (int y = origin.y; y > endpoint.y; y--) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX - reversegradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	unsigned int color = 0xff000000;
	double currentY = origin.y;
	for (int x = origin.x; x > endpoint.x; x--) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY - gradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	unsigned int color = 0xff000000;
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	for (int y = origin.y; y < endpoint.y; y++) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX + reversegradient;
	}
	drawable->updateScreen();
}


