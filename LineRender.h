#pragma once
#include <map>
#include "MathWiz.h"
#include "OctantWiz.h"
#include "renderarea361.h"
#include "client.h"

namespace LineRenderer {

	struct FillPack {
		std::map<int, int> map;
		bool xiter;
		bool movepositive;

		FillPack() {}

		FillPack(std::map<int, int> some_map, bool something, bool move) {
			map = some_map;
			xiter = something;
			movepositive = move;
		}
	};

	void DDArender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color);
	void BRErender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color);
	void AArender(Drawable *drawable, int x1, int y1, int x2, int y2, unsigned int color);
	FillPack PolyDDArender(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, unsigned int color);
	//TODO AArender
	//TODO Remove all bit-shifting multiplication and write them as integer multiplication

	//Octant Renders for DDA
	void RenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void RenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void RenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void RenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);


	//Octant Renders for Bresenham's 
	void BRenderOctant1(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant2(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant4(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant6(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void BRenderOctant8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	

	//Polygon-filling Line Renders

	FillPack PolyRenderOctant1Or8(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	FillPack PolyRenderOctant2Or3(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	FillPack PolyRenderOctant4Or5(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	FillPack PolyRenderOctant6Or7(Drawable *drawable, OctantWiz::Point origin, OctantWiz::Point endpoint, double gradient, unsigned int color);
	void FillBetweenLines(Drawable *drawable, std::vector<OctantWiz::Point> line1, std::vector<OctantWiz::Point> line2, unsigned int color);
}