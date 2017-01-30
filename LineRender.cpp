#include "LineRender.h"

unsigned int color = 0xff000000;             //Black color

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

void LineRenderer::BRErender(Drawable *drawable, int x1, int y1, int x2, int y2) {
	OctantWiz::Point origin(x1, y1);
	OctantWiz::Point endpoint(x2, y2);
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(x2 - x1, y2 - y1);

	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {                              //rather ugly switch
	case OctantWiz::Octant::OctantOne:
		BRenderOctant1(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantTwo:
		BRenderOctant2(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantThree:
		BRenderOctant3(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantFour:
		BRenderOctant4(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantFive:
		BRenderOctant5(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantSix:
		BRenderOctant6(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantSeven:
		BRenderOctant7(drawable, origin, endpoint, gradient);
		break;
	case OctantWiz::Octant::OctantEight:
		BRenderOctant8(drawable, origin, endpoint, gradient);
		break;
	}
}

void LineRenderer::AArender(Drawable *drawable, int x1, int y1, int x2, int y2) {
	bool steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep) {
		MathWiz::swap(x1, y1);
		MathWiz::swap(x2, y2);
	}
	if (x1 > x2) {
		MathWiz::swap(x1, x2);
		MathWiz::swap(y1, y2);
	}
	

	int dx = x2 - x1;
	int dy = y2 - y1;
	double gradient = dy / dx;

	if (dx == 0.0) {
		gradient = 1.0;
	}

	//handle first endpoint
	double xend = round(x1);
	double yend = y1 + gradient * (xend - x1);
	double xgap = MathWiz::rfpart(x1 + 0.5);
	double xpxl1 = xend;      //used in main loop
	int ypxl1 = static_cast<int>(yend);

	if (steep) {
		drawable->setPixel(ypxl1, xpxl1, MathWiz::alphatoblackvar(MathWiz::rfpart(yend) * xgap));
		drawable->setPixel(ypxl1 + 1, xpxl1, MathWiz::alphatoblackvar(MathWiz::fpart(yend) * xgap));
	}
	else {
		drawable->setPixel(xpxl1, ypxl1, MathWiz::alphatoblackvar(MathWiz::rfpart(yend) * xgap));
		drawable->setPixel(xpxl1, ypxl1 + 1, MathWiz::alphatoblackvar(MathWiz::fpart(yend) * xgap));
	}
	double intery = yend + gradient;    //first intersection for the main loop

	//handle second endpoint
	xend = round(x2);
	yend = y2 + gradient * (xend - x2);
	xgap = MathWiz::fpart(x2 + 0.5);
	double xpxl2 = xend;
	int ypxl2 = static_cast<int>(yend);

	if (steep) {
		drawable->setPixel(ypxl2, xpxl2, MathWiz::alphatoblackvar(MathWiz::rfpart(yend) * xgap));
		drawable->setPixel(ypxl2 + 1, xpxl2, MathWiz::alphatoblackvar(MathWiz::fpart(yend) * xgap));
	}
	else {
		drawable->setPixel(xpxl2, ypxl2, MathWiz::alphatoblackvar(MathWiz::rfpart(yend) * xgap));
		drawable->setPixel(xpxl2, ypxl2 + 1, MathWiz::alphatoblackvar(MathWiz::fpart(yend) * xgap));
	}

	//main loop
	if (steep) {
		for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
			drawable->setPixel(static_cast<int>(intery), x, MathWiz::alphatoblackvar(MathWiz::rfpart(intery)));
			drawable->setPixel(static_cast<int>(intery) + 1, x, MathWiz::alphatoblackvar(MathWiz::fpart(intery)));
			intery = intery + gradient;
		}
	}
	else {
		for (int x = xpxl1 + 1; x <= xpxl2 - 1; x++) {
			drawable->setPixel(x, static_cast<int>(intery), MathWiz::alphatoblackvar(MathWiz::rfpart(intery)));
			drawable->setPixel(x, static_cast<int>(intery) + 1, MathWiz::alphatoblackvar(MathWiz::fpart(intery)));
			intery = intery + gradient;
		}
	}
}

void LineRenderer::RenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	double currentY = origin.y;
	for (int x = origin.x; x <= endpoint.x; x++) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY + gradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	for (int y = origin.y; y >= endpoint.y; y--) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX - reversegradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	double currentY = origin.y;
	for (int x = origin.x; x >= endpoint.x; x--) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY - gradient;
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;
	for (int y = origin.y; y <= endpoint.y; y++) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX + reversegradient;
	}
	drawable->updateScreen();
}

void LineRenderer::BRenderOctant1(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant2(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant4(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant6(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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

void LineRenderer::BRenderOctant8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
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
