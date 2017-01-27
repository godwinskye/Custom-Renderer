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
