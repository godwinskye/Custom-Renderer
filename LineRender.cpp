#include "LineRender.h"


void LineRenderer::DDArender(Client Client,int x1, int y1, int x2, int y2) {
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

	OctantWiz::Octant target = OctantWiz::FindOctant(endpoint);

	switch (target) {
	case OctantWiz::Octant::OctantOne:
		RenderOctant1(Client, origin, endpoint, gradient);
	//case OctantWiz::Octant::OctantTwo:

	}
}

void LineRenderer::RenderOctant1(Client Client, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient) {
	unsigned int color = 0xff000000;      //Black color
	double currentY = origin.y;
	for (int x = origin.x; x < endpoint.x; x++) {
		//setpixel
		Client.drawable->setPixel(x, round(currentY), color);
		currentY = currentY + gradient;
	}
	Client.drawable->updateScreen();
}
