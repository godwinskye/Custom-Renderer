#pragma once
#include <map>
#include "../MathWiz/MathWiz.h"
#include "../OctantWiz/OctantWiz.h"
#include "renderarea361.h"
#include "client.h"
#include "../Renderer/PolyFill.h"

namespace LineRenderer {

	struct FillPack {
		std::map<int, int> map;
		bool xiter;
		bool movepositive;
		OctantWiz::Point origin;
		OctantWiz::Point endpoint;

		FillPack() {}

		FillPack(std::map<int, int> some_map, bool something, bool move, OctantWiz::Point pt1, OctantWiz::Point pt2) {
			map = some_map;
			xiter = something;
			movepositive = move;
			origin = pt1;
			endpoint = pt2;
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
	PolyFill::LongestTriLine FindLongest(LineRenderer::FillPack line1, LineRenderer::FillPack line2, LineRenderer::FillPack line3);
	bool TestForLongest(LineRenderer::FillPack line1, LineRenderer::FillPack line2, LineRenderer::FillPack line3);
}