#pragma once
#include "LineRender.h"

namespace LineRenderer {
	void LiDDArender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color1, unsigned int color2);
	FillPack LiPolyDDArender(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, unsigned int color1, unsigned int color2);

	//Octant Renders with Linear Interpolation
	void LiRenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	void LiRenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	void LiRenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	void LiRenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);

	//Tools for LiPolyFill
	FillPack LiPolyRenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	FillPack LiPolyRenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	FillPack LiPolyRenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
	FillPack LiPolyRenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color1, unsigned int color2);
}