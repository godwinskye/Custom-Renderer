#pragma once
#include "MathWiz.h"
#include "OctantWiz.h"
#include "renderarea361.h"
#include "client.h"

namespace LineRenderer {
	void DDArender(Drawable *drawable, int x1, int y1, int x2, int y2);


	//Octant Renders for DDA
	void RenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);

	//Octant Renders for Bresenham's 
	void BRenderOctant1(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void TRenderOctant1(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
}