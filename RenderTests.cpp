#include "RenderTests.h"

void RenderTests::DDAStarburstTest(Drawable * drawable, int x, int y, unsigned int length, unsigned int numberoflines) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	for (int i = 0; i < numberoflines; i++) {
		OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
		LineRenderer::DDArender(drawable, x, y, endpoint.x, endpoint.y);
		currentangle = currentangle + angleinc;
	}
}

void RenderTests::BRStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	for (int i = 0; i < numberoflines; i++) {
		OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
		LineRenderer::BRErender(drawable, x, y, endpoint.x, endpoint.y);
		currentangle = currentangle + angleinc;
	}
}

void RenderTests::MixStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;
	int flag = 0;

	for (int i = 0; i < numberoflines; i++) {
		if (flag % 2 == 0) {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			LineRenderer::DDArender(drawable, x, y, endpoint.x, endpoint.y);
			currentangle = currentangle + angleinc;
		}
		else {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			LineRenderer::BRErender(drawable, x, y, endpoint.x, endpoint.y);
			currentangle = currentangle + angleinc;
		}
		flag = flag + 1;
	}
}

void RenderTests::AAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	for (int i = 0; i < numberoflines; i++) {
		OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
		LineRenderer::AArender(drawable, x, y, endpoint.x, endpoint.y);
		currentangle = currentangle + angleinc;
	}
}

void RenderTests::DDAParallelogramTest(Drawable *drawable, int x, int y) {
	for (int i = 0; i < 50; i++) {
		LineRenderer::DDArender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i);
		LineRenderer::DDArender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40);
	}
}

void RenderTests::BREParallelogramTest(Drawable *drawable, int x, int y) {
	for (int i = 0; i < 50; i++) {
		LineRenderer::BRErender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i);
		LineRenderer::BRErender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40);
	}
}

void RenderTests::MixParallelogramTest(Drawable *drawable, int x, int y) {
	unsigned int flag = 0;
	for (int i = 0; i < 50; i++) {
		if (flag % 2 == 0) {
			LineRenderer::DDArender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i);
			LineRenderer::DDArender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40);
		}
		else {
			LineRenderer::BRErender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i);
			LineRenderer::BRErender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40);
		}
		flag = flag + 1;
	}
}
