#pragma once
#include "MathWiz.h"
#include "OctantWiz.h"
#include "renderarea361.h"
#include "client.h"

namespace LineRenderer {
	void DDArender(Client Client, int x1, int y1, int x2, int y2);


	//Octant Renders
	void RenderOctant1Or8(Client Client, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant2Or3(Client Client, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant4Or5(Client Client, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant6Or7(Client Client, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
}