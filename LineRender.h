#pragma once
#include "MathWiz.h"
#include "OctantWiz.h"
#include "renderarea361.h"
#include "client.h"

namespace LineRenderer {
	void DDArender(Client Client, int x1, int y1, int x2, int y2);


	//Octant Renders
	void RenderOctant1(Client Client, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient);
	void RenderOctant2(OctantWiz::Point origin, OctantWiz::Point endpoint);
	void RenderOctant3(OctantWiz::Point origin, OctantWiz::Point endpoint);
	void RenderOctant4(OctantWiz::Point origin, OctantWiz::Point endpoint);
	void RenderOctant5(OctantWiz::Point origin, OctantWiz::Point endpoint);
	void RenderOctant6(OctantWiz::Point origin, OctantWiz::Point endpoint);
	void RenderOctant7(OctantWiz::Point origin, OctantWiz::Point endpoint);
	void RenderOctant8(OctantWiz::Point origin, OctantWiz::Point endpoint);
}