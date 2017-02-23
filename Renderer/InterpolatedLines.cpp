#include "InterpolatedLines.h"

void LineRenderer::LiDDArender(Drawable * drawable, int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2) {
	OctantWiz::Point origin(x1, y1);
	OctantWiz::Point endpoint(x2, y2);
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(x2 - x1, y2 - y1);
	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {							//rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		LiRenderOctant1Or8(drawable, origin, endpoint, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		LiRenderOctant2Or3(drawable, origin, endpoint, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		LiRenderOctant4Or5(drawable, origin, endpoint, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		LiRenderOctant6Or7(drawable, origin, endpoint, gradient, color1, color2);
		break;
	}
}

void LineRenderer::LiRenderOctant1Or8(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentY = origin.y;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.x - origin.x);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.x - origin.x);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.x - origin.x);
	
	double color = static_cast<double>(color1);
	for (int x = origin.x; x <= endpoint.x; x++) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY + gradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

void LineRenderer::LiRenderOctant2Or3(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.y - origin.y);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.y - origin.y);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.y - origin.y);

	double color = static_cast<double>(color1);
	for (int y = origin.y; y >= endpoint.y; y--) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX - reversegradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

void LineRenderer::LiRenderOctant4Or5(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentY = origin.y;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.x - origin.x);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.x - origin.x);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.x - origin.x);

	double color = static_cast<double>(color1);
	for (int x = origin.x; x >= endpoint.x; x--) {
		drawable->setPixel(x, round(currentY), color);
		currentY = currentY - gradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

void LineRenderer::LiRenderOctant6Or7(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.y - origin.y);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.y - origin.y);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.y - origin.y);

	double color = static_cast<double>(color1);
	for (int y = origin.y; y <= endpoint.y; y++) {
		drawable->setPixel(round(currentX), y, color);
		currentX = currentX + reversegradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}
