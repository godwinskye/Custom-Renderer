#pragma once
#include "../OctantWiz/OctantWiz.h"
#include "../MathWiz/MathWiz.h"
#include "renderarea361.h"

namespace PolyFill {

	void PrePolySort(std::vector<OctantWiz::Point>& list);
	void PrePolySort3D(std::vector<OctantWiz::Point3D>& list);

	void Triangle(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color);
}