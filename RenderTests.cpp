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