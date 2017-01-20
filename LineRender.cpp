#include "LineRender.h"


void LineRenderer::DDArender(int x1, int y1, int x2, int y2) {
	OctantWiz::Point origin(x1, y1);
	OctantWiz::Point endpoint(x2, y2);
	double gradient = MathWiz::GetGradient(origin, endpoint);

	/* SCRAPPED
	double currentY = y1;

	
	for (int x = x1; x < x2; x++) {
		OctantWiz::SetPixelByOctant(origin, endpoint, x, round(currentY);
		currentY = currentY + gradient;
	}

	*/

	OctantWiz::Octant target = 
}
