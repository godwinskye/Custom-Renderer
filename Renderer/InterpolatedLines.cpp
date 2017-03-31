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

LineRenderer::FillPack LineRenderer::LiPolyDDArender(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, unsigned int color1, unsigned int color2) {
	double gradient = MathWiz::GetGradient(origin, endpoint);
	OctantWiz::Point diffpoint(endpoint.x - origin.x, endpoint.y - origin.y);
	FillPack line;

	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {                              //rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		line = LiPolyRenderOctant1Or8(drawable, origin, endpoint, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		line = LiPolyRenderOctant2Or3(drawable, origin, endpoint, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		line = LiPolyRenderOctant4Or5(drawable, origin, endpoint, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		line = LiPolyRenderOctant6Or7(drawable, origin, endpoint, gradient, color1, color2);
		break;
	}
	return line;
}

void LineRenderer::LiRenderOctant1Or8(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentY = origin.y;

	//Color interpolation
	int range = endpoint.x - origin.x;
	Color color(color1);
	Color colorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
	
	for (int x = origin.x; x <= endpoint.x; x++) {
		drawable->setPixel(x, round(currentY), color.getHex());
		currentY = currentY + gradient;

		color.AddColor(colorgradient);
	}
	drawable->updateScreen();
}

void LineRenderer::LiRenderOctant2Or3(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;

	//Color interpolation
	int range = endpoint.y - origin.y;
	Color color(color1);
	Color colorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);

	for (int y = origin.y; y >= endpoint.y; y--) {
		drawable->setPixel(round(currentX), y, color.getHex());
		currentX = currentX - reversegradient;

		color.AddColor(colorgradient);
	}
	drawable->updateScreen();
}

void LineRenderer::LiRenderOctant4Or5(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentY = origin.y;

	//Color interpolation
	int range = endpoint.x - origin.x;
	Color color(color1);
	Color colorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);

	for (int x = origin.x; x >= endpoint.x; x--) {
		drawable->setPixel(x, round(currentY), color.getHex());
		currentY = currentY - gradient;

		color.AddColor(colorgradient);
	}
	drawable->updateScreen();
}

void LineRenderer::LiRenderOctant6Or7(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	double currentX = origin.x;
	double reversegradient = 1 / gradient;

	//Color interpolation
	int range = endpoint.y - origin.y;
	Color color(color1);
	Color colorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);

	for (int y = origin.y; y <= endpoint.y; y++) {
		drawable->setPixel(round(currentX), y, color.getHex());
		currentX = currentX + reversegradient;

		color.AddColor(colorgradient);
	}
	drawable->updateScreen();
}

LineRenderer::FillPack LineRenderer::LiPolyRenderOctant1Or8(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = true;
	bool movepositive = true;
	
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
		line1.insert(std::pair<int, int>(x, round(currentY)));
		currentY = currentY + gradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(blue)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack LineRenderer::LiPolyRenderOctant2Or3(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = false;
	bool movepositive = false;
	
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
		line1.insert(std::pair<int, int>(y, round(currentX)));
		currentX = currentX - reversegradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(blue)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack LineRenderer::LiPolyRenderOctant4Or5(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = true;
	bool movepositive = false;
	
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
		line1.insert(std::pair<int, int>(x, round(currentY)));
		currentY = currentY - gradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(blue)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack LineRenderer::LiPolyRenderOctant6Or7(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = false;
	bool movepositive = true;
	
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
		line1.insert(std::pair<int, int>(y, round(currentX)));
		currentX = currentX + reversegradient;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(blue)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack(line1, xiter, movepositive, origin, endpoint);
}

void LineRenderer::LiDDArender3D(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, unsigned int color1, unsigned int color2) {
	double gradient = MathWiz::GetGradient3D(origin, endpoint);
	OctantWiz::Point diffpoint(endpoint.x - origin.x, endpoint.y - origin.y);
	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {							//rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		RenderOctant3D1Or8(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		RenderOctant3D2Or3(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		RenderOctant3D4Or5(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		RenderOctant3D6Or7(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	}
}

void LineRenderer::LiDDArender3D(Drawable * drawable, int x1, int y1, int z1, int x2, int y2, int z2, Matrix & zBuffer, unsigned int color1, unsigned int color2) {
	OctantWiz::Point3D origin(x1, y1, z1);
	OctantWiz::Point3D endpoint(x2, y2, z2);
	double gradient = MathWiz::GetGradient3D(origin, endpoint);
	OctantWiz::Point diffpoint(endpoint.x - origin.x, endpoint.y - origin.y);
	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);

	switch (target) {							//rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		RenderOctant3D1Or8(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		RenderOctant3D2Or3(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		RenderOctant3D4Or5(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		RenderOctant3D6Or7(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	}
}

LineRenderer::FillPack3D LineRenderer::PolyDDArender3D(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix & zBuffer, unsigned int color1, unsigned int color2) {
	double gradient = MathWiz::GetGradient3D(origin, endpoint);
	OctantWiz::Point diffpoint(endpoint.x - origin.x, endpoint.y - origin.y);
	OctantWiz::Octant target = OctantWiz::FindOctant(diffpoint);
	FillPack3D line;

	switch (target) {							//rather ugly switch
	case OctantWiz::Octant::OctantOne:
	case OctantWiz::Octant::OctantEight:
		line = PolyRenderOctant3D1Or8(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantTwo:
	case OctantWiz::Octant::OctantThree:
		line = PolyRenderOctant3D2Or3(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantFour:
	case OctantWiz::Octant::OctantFive:
		line = PolyRenderOctant3D4Or5(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	case OctantWiz::Octant::OctantSix:
	case OctantWiz::Octant::OctantSeven:
		line = PolyRenderOctant3D6Or7(drawable, origin, endpoint, zBuffer, gradient, color1, color2);
		break;
	}
	return line;
}

void LineRenderer::RenderOctant3D1Or8(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2) {
	double currentY = origin.y;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.x - origin.x);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.x - origin.x);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.x - origin.x);

	double color = static_cast<double>(color1);

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.x - origin.x));

	for (int x = origin.x; x <= endpoint.x; x++) {
		if (currentZ < zBuffer.at(x, round(currentY))) {
			drawable->setPixel(x, round(currentY), color);
			zBuffer.setAt(x, round(currentY), currentZ);
		}
		currentY = currentY + gradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant3D2Or3(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2) {
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

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.y - origin.y));

	for (int y = origin.y; y >= endpoint.y; y--) {
		if (currentZ < zBuffer.at(round(currentX), y)) {
			drawable->setPixel(round(currentX), y, color);
			zBuffer.setAt(round(currentX), y, currentZ);
		}
		currentX = currentX - reversegradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant3D4Or5(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2) {
	double currentY = origin.y;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.x - origin.x);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.x - origin.x);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.x - origin.x);

	double color = static_cast<double>(color1);

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.x - origin.x));

	for (int x = origin.x; x >= endpoint.x; x--) {
		if (currentZ < zBuffer.at(x, round(currentY))) {
			drawable->setPixel(x, round(currentY), color);
			zBuffer.setAt(x, round(currentY), currentZ);
		}
		currentY = currentY - gradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

void LineRenderer::RenderOctant3D6Or7(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix& zBuffer, double gradient, unsigned int color1, unsigned int color2) {
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

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.y - origin.y));

	for (int y = origin.y; y <= endpoint.y; y++) {
		if (currentZ < zBuffer.at(round(currentX), y)) {
			drawable->setPixel(round(currentX), y, color);
			zBuffer.setAt(round(currentX), y, currentZ);
		}
		currentX = currentX + reversegradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
}

LineRenderer::FillPack3D LineRenderer::PolyRenderOctant3D1Or8(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix & zBuffer, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = true;
	bool movepositive = true;
	
	double currentY = origin.y;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.x - origin.x);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.x - origin.x);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.x - origin.x);

	double color = static_cast<double>(color1);

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.x - origin.x));

	for (int x = origin.x; x <= endpoint.x; x++) {
		if (currentZ < zBuffer.at(x, round(currentY))) {
			drawable->setPixel(x, round(currentY), color);
			zBuffer.setAt(x, round(currentY), round(currentZ));
		}
		line1.insert(std::pair<int, int>(x, round(currentY)));
		currentY = currentY + gradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack3D(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack3D LineRenderer::PolyRenderOctant3D2Or3(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix & zBuffer, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = false;
	bool movepositive = false;
	
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

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.y - origin.y));

	for (int y = origin.y; y >= endpoint.y; y--) {
		if (currentZ < zBuffer.at(round(currentX), y)) {
			drawable->setPixel(round(currentX), y, color);
			zBuffer.setAt(round(currentX), y, currentZ);
		}
		line1.insert(std::pair<int, int>(y, round(currentX)));
		currentX = currentX - reversegradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack3D(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack3D LineRenderer::PolyRenderOctant3D4Or5(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix & zBuffer, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = true;
	bool movepositive = false;
	
	double currentY = origin.y;

	//Color interpolation
	double red = (color1 >> 16) & 0xff;
	double green = (color1 >> 8) & 0xff;
	double blue = color1 & 0xff;
	double redgradient = (((color2 >> 16) & 0xff) - red) / (endpoint.x - origin.x);
	double greengradient = (((color2 >> 8) & 0xff) - green) / (endpoint.x - origin.x);
	double bluegradient = ((color2 & 0xff) - blue) / (endpoint.x - origin.x);

	double color = static_cast<double>(color1);

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.x - origin.x));

	for (int x = origin.x; x >= endpoint.x; x--) {
		if (currentZ < zBuffer.at(x, round(currentY))) {
			drawable->setPixel(x, round(currentY), color);
			zBuffer.setAt(x, round(currentY), currentZ);
		}
		line1.insert(std::pair<int, int>(x, round(currentY)));
		currentY = currentY - gradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack3D(line1, xiter, movepositive, origin, endpoint);
}

LineRenderer::FillPack3D LineRenderer::PolyRenderOctant3D6Or7(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint, Matrix & zBuffer, double gradient, unsigned int color1, unsigned int color2) {
	std::map<int, int> line1;
	bool xiter = false;
	bool movepositive = true;
	
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

	//Z-component
	double currentZ = origin.z;
	double dz = static_cast<double>((endpoint.z - origin.z) / (endpoint.y - origin.y));

	for (int y = origin.y; y <= endpoint.y; y++) {
		if (currentZ < zBuffer.at(round(currentX), y)) {
			drawable->setPixel(round(currentX), y, color);
			zBuffer.setAt(round(currentX), y, currentZ);
		}
		line1.insert(std::pair<int, int>(y, round(currentX)));
		currentX = currentX + reversegradient;
		currentZ = currentZ + dz;

		red = red + redgradient;
		green = green + greengradient;
		blue = blue + bluegradient;
		color = (0xff << 24) + ((static_cast<int>(round(red)) & 0xff) << 16) + ((static_cast<int>(round(green)) & 0xff) << 8) + (static_cast<int>(round(green)) & 0xff);
	}
	drawable->updateScreen();
	return FillPack3D(line1, xiter, movepositive, origin, endpoint);
}
