#pragma once
#include "PolyFill.h"

namespace PolyFill {
	void LiTriangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color1, unsigned int color2, unsigned int color3);

	void Triangle3D(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2, Matrix& zBuffer, unsigned int color1, unsigned int color2, unsigned int color3);
	void WireTriangle3D(Drawable *drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2, Matrix& zBuffer, unsigned int color1, unsigned int color2, unsigned int color3);
}