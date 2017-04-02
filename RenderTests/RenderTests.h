#pragma once
#include "../Renderer/PolyFill.h"
#include <vector>

namespace RenderTests {

	struct RandomTestPackage {
		std::vector<unsigned int> xcoord;
		std::vector<unsigned int> xendcoord;
		std::vector<unsigned int> ycoord;
		std::vector<unsigned int> yendcoord;
		std::vector<unsigned int> color;

		RandomTestPackage(std::vector<unsigned int> &xcoords, std::vector<unsigned int> &ycoords, std::vector<unsigned int> &xendcoords, std::vector<unsigned int> &yendcoords, std::vector<unsigned int> &colors) {
			xcoord = xcoords;
			ycoord = ycoords;
			xendcoord = xendcoords;
			yendcoord = yendcoords;
			color = colors;
		}
	};

	//Starburst Tests
	void DDAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color);
	void BRStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color);
	void MixStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color);
	void AAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color);

	//Parallelogram Test
	void DDAParallelogramTest(Drawable *drawable, int x, int y, unsigned int color);
	void BREParallelogramTest(Drawable *drawable, int x, int y, unsigned int color);
	void MixParallelogramTest(Drawable *drawable, int x, int y, unsigned int color);

	//Random Test
	RandomTestPackage GetPackage();
	void DDARandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y);
	void BRERandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y);
	void MixRandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y);
	void AARandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y);

	//Filling Polygons
	void PolygonStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines);
	void Triangles162Test(Drawable *drawable, int xstart, int ystart);
	void TransTriangles162Test(Drawable *drawable, int xstart, int ystart);
	void RandomPolyTest(Drawable *drawable, int x, int y, unsigned int numberofpoly);

	//Interpolation Tests
	void TransWireframeTri162Test(Drawable *drawable, int xstart, int ystart);
	void TransMeshTri162Test(Drawable *drawable, int xstart, int ystart);

	//TODO: zBuffer-3D Test
	void zBufferTest(Drawable* drawable);
}