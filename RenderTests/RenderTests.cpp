#include "RenderTests.h"
#include "../Renderer/InterpolatedLines.h"
#include "../Renderer/InterpolatedPolyFill.h"

void RenderTests::DDAStarburstTest(Drawable * drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	for (int i = 0; i < numberoflines; i++) {
		OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
		LineRenderer::DDArender(drawable, x, y, endpoint.x, endpoint.y, color);
		currentangle = currentangle + angleinc;
	}
}

void RenderTests::BRStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	for (int i = 0; i < numberoflines; i++) {
		OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
		LineRenderer::BRErender(drawable, x, y, endpoint.x, endpoint.y, color);
		currentangle = currentangle + angleinc;
	}
}

void RenderTests::MixStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;
	int flag = 0;

	for (int i = 0; i < numberoflines; i++) {
		if (flag % 2 == 0) {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			LineRenderer::DDArender(drawable, x, y, endpoint.x, endpoint.y, color);
			currentangle = currentangle + angleinc;
		}
		else {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			LineRenderer::BRErender(drawable, x, y, endpoint.x, endpoint.y, color);
			currentangle = currentangle + angleinc;
		}
		flag = flag + 1;
	}
}

void RenderTests::AAStarburstTest(Drawable *drawable, int x, int y, unsigned int length, unsigned int numberoflines, unsigned int color) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	for (int i = 0; i < numberoflines; i++) {
		OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
		LineRenderer::AArender(drawable, x, y, endpoint.x, endpoint.y, color);
		currentangle = currentangle + angleinc;
	}
}

void RenderTests::DDAParallelogramTest(Drawable *drawable, int x, int y, unsigned int color) {
	for (int i = 0; i < 50; i++) {
		LineRenderer::DDArender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i, color);
		LineRenderer::DDArender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40, color);
	}
}

void RenderTests::BREParallelogramTest(Drawable *drawable, int x, int y, unsigned int color) {
	for (int i = 0; i < 50; i++) {
		LineRenderer::BRErender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i, color);
		LineRenderer::BRErender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40, color);
	}
}

void RenderTests::MixParallelogramTest(Drawable *drawable, int x, int y, unsigned int color) {
	unsigned int flag = 0;
	for (int i = 0; i < 50; i++) {
		if (flag % 2 == 0) {
			LineRenderer::DDArender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i, color);
			LineRenderer::DDArender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40, color);
		}
		else {
			LineRenderer::BRErender(drawable, x + 20, y + 80 + i, x + 150, y + 150 + i, color);
			LineRenderer::BRErender(drawable, x + 160 + i, y + 270, x + 240 + i, y + 40, color);
		}
		flag = flag + 1;
	}
}

RenderTests::RandomTestPackage RenderTests::GetPackage() {
	const unsigned int numberoflines = 30;
	const unsigned int lowerboundary = 0;
	const unsigned int upperboundary = 300;

	std::vector<unsigned int> xcoord(numberoflines), ycoord(numberoflines);
	std::vector<unsigned int> xendcoord(numberoflines), yendcoord(numberoflines);
	std::vector<unsigned int> color(numberoflines);

	for (int i = 0; i < numberoflines; i++) {
		xcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		ycoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		xendcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		yendcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		color[i] = MathWiz::RandomRGBHex();
	}
	RenderTests::RandomTestPackage package = RenderTests::RandomTestPackage(xcoord, ycoord, xendcoord, yendcoord, color);
	return package;
}

void RenderTests::DDARandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y) {
	unsigned int size = package.color.size();        //can be size of any element in package

	for (int i = 0; i < size; i++) {
		LineRenderer::DDArender(drawable, origin_x + package.xcoord[i], origin_y + package.ycoord[i], origin_x + package.xendcoord[i], origin_y + package.yendcoord[i], package.color[i]);
	}
}

void RenderTests::BRERandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y) {
	unsigned int size = package.color.size();

	for (int i = 0; i < size; i++) {
		LineRenderer::BRErender(drawable, origin_x + package.xcoord[i], origin_y + package.ycoord[i], origin_x + package.xendcoord[i], origin_y + package.yendcoord[i], package.color[i]);
	}
}

void RenderTests::MixRandomTest(Drawable * drawable, RandomTestPackage package, int origin_x, int origin_y) {
	unsigned int size = package.color.size();
	unsigned int flag = 0;

	for (int i = 0; i < size; i++) {
		if (flag % 2 == 0) {
			LineRenderer::DDArender(drawable, origin_x + package.xcoord[i], origin_y + package.ycoord[i], origin_x + package.xendcoord[i], origin_y + package.yendcoord[i], package.color[i]);
		}
		else {
			LineRenderer::BRErender(drawable, origin_x + package.xcoord[i], origin_y + package.ycoord[i], origin_x + package.xendcoord[i], origin_y + package.yendcoord[i], package.color[i]);
		}
		flag = flag + 1;
	}
}

void RenderTests::AARandomTest(Drawable *drawable, RandomTestPackage package, int origin_x, int origin_y) {
	unsigned int size = package.color.size();

	for (int i = 0; i < size; i++) {
		LineRenderer::AArender(drawable, origin_x + package.xcoord[i], origin_y + package.ycoord[i], origin_x + package.xendcoord[i], origin_y + package.yendcoord[i], package.color[i]);
	}
}

void RenderTests::PolygonStarburstTest(Drawable * drawable, int x, int y, unsigned int length, unsigned int numberoflines) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	OctantWiz::Point origin(x, y);
	OctantWiz::Point endpoint1;
	OctantWiz::Point endpoint2;

	for (int i = 0; i < numberoflines + 1; i++) {
		if (i % 2 == 0) {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			endpoint1 = endpoint;
			currentangle = currentangle + angleinc;
		}
		else {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			endpoint2 = endpoint;
			currentangle = currentangle + angleinc;
		}
		if (i > 0) {
			PolyFill::Triangle(drawable, origin, endpoint1, endpoint2, 0xffffffff);
		}
	}
}

void RenderTests::Triangles162Test(Drawable *drawable, int xstart, int ystart) {
	const int numbereachrow = 10;
	std::vector<OctantWiz::Point> rowpoints(numbereachrow);
	std::vector<std::vector<OctantWiz::Point>> wholearray;
	OctantWiz::Point first(xstart + 40, ystart + 40);
	int tempY = first.y;

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			rowpoints[j] = OctantWiz::Point(first.x + 25 * j, tempY);
		}
		tempY = tempY + 25;
		wholearray.push_back(rowpoints);
	}
	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			unsigned int color = MathWiz::RandomRGBHex();
			unsigned int color2 = MathWiz::RandomRGBHex();
			if (j > 0) {
				LineRenderer::DDArender(drawable, wholearray[i][j - 1].x, wholearray[i][j - 1].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0) {
				LineRenderer::DDArender(drawable, wholearray[i - 1][j].x, wholearray[i - 1][j].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0 && j > 0) {
				PolyFill::Triangle(drawable, wholearray[i][j], wholearray[i - 1][j], wholearray[i - 1][j - 1], color);
				PolyFill::Triangle(drawable, wholearray[i][j - 1], wholearray[i - 1][j - 1], wholearray[i][j], color2);
			}
		}
	}
}

void RenderTests::TransTriangles162Test(Drawable *drawable, int xstart, int ystart) {
	const int numbereachrow = 10;
	std::vector<OctantWiz::Point> rowpoints(numbereachrow);
	std::vector<std::vector<OctantWiz::Point>> wholearray;
	OctantWiz::Point first(xstart + 40, ystart + 40);
	int tempY = first.y;
	int translate;
	int upper = 12;
	int lower = -12;

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			rowpoints[j] = OctantWiz::Point(first.x + 25 * j, tempY);
		}
		tempY = tempY + 25;
		wholearray.push_back(rowpoints);
	}

	//translate by [-12, 12]
	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			translate = rand() % ((upper - lower) + 1) + lower;
			wholearray[i][j].x = wholearray[i][j].x + translate;
			wholearray[i][j].y = wholearray[i][j].y + translate;
		}
	}

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			unsigned int color = MathWiz::RandomRGBHex();
			unsigned int color2 = MathWiz::RandomRGBHex();
			if (j > 0) {
				LineRenderer::DDArender(drawable, wholearray[i][j - 1].x, wholearray[i][j - 1].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0) {
				LineRenderer::DDArender(drawable, wholearray[i - 1][j].x, wholearray[i - 1][j].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0 && j > 0) {
				PolyFill::Triangle(drawable, wholearray[i][j], wholearray[i - 1][j], wholearray[i - 1][j - 1], color);
				PolyFill::Triangle(drawable, wholearray[i][j - 1], wholearray[i - 1][j - 1], wholearray[i][j], color2);
			}
		}
	}
}

void RenderTests::RandomPolyTest(Drawable * drawable, int x, int y, unsigned int numberofpoly) {
	const unsigned int numberoftri = numberofpoly;
	const unsigned int lowerboundary = 0;
	const unsigned int upperboundary = 300;
	OctantWiz::Point point1();
	OctantWiz::Point point2();
	OctantWiz::Point point3();

	std::vector<unsigned int> xcoord(numberoftri), ycoord(numberoftri);
	std::vector<unsigned int> xendcoord(numberoftri), yendcoord(numberoftri);
	std::vector<unsigned int> xendcoord2(numberoftri), yendcoord2(numberoftri);

	for (int i = 0; i < numberoftri; i++) {
		xcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		ycoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		xendcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		yendcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		xendcoord2[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		yendcoord2[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
	}

	for (int i = 0; i < numberoftri; i++) {
		PolyFill::Triangle(drawable, OctantWiz::Point(xcoord[i] + x, ycoord[i] + y), OctantWiz::Point(xendcoord[i] + x, yendcoord[i] + y), OctantWiz::Point(xendcoord2[i] + x, yendcoord2[i] + y), MathWiz::RandomRGBHex());
	}
}


//For page 5 blend with white tests

void RenderTests::BPolygonStarburstTest(Drawable * drawable, int x, int y, unsigned int length, unsigned int numberoflines) {
	const double angleinc = (2 * M_PI) / numberoflines;
	double currentangle = 0;

	OctantWiz::Point origin(x, y);
	OctantWiz::Point endpoint1;
	OctantWiz::Point endpoint2;

	for (int i = 0; i < numberoflines; i++) {
		if (i % 2 == 0) {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			endpoint1 = endpoint;
			currentangle = currentangle + angleinc;
		}
		else {
			OctantWiz::Point endpoint = MathWiz::DetermineEndPoint(currentangle, length, x, y);
			endpoint2 = endpoint;
			currentangle = currentangle + angleinc;
		}
		if (i > 0) {
			PolyFill::BTriangle(drawable, origin, endpoint1, endpoint2, MathWiz::RandomRGBHex());
		}
	}
}

void RenderTests::BTriangles162Test(Drawable * drawable, int xstart, int ystart) {
	const int numbereachrow = 10;
	std::vector<OctantWiz::Point> rowpoints(numbereachrow);
	std::vector<std::vector<OctantWiz::Point>> wholearray;
	OctantWiz::Point first(xstart + 40, ystart + 40);
	int tempY = first.y;

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			rowpoints[j] = OctantWiz::Point(first.x + 25 * j, tempY);
		}
		tempY = tempY + 25;
		wholearray.push_back(rowpoints);
	}
	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			unsigned int color = MathWiz::RandomRGBHex();
			unsigned int color2 = MathWiz::RandomRGBHex();
			if (j > 0) {
				LineRenderer::DDArender(drawable, wholearray[i][j - 1].x, wholearray[i][j - 1].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0) {
				LineRenderer::DDArender(drawable, wholearray[i - 1][j].x, wholearray[i - 1][j].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0 && j > 0) {
				PolyFill::BTriangle(drawable, wholearray[i][j], wholearray[i - 1][j], wholearray[i - 1][j - 1], color);
				PolyFill::BTriangle(drawable, wholearray[i][j - 1], wholearray[i - 1][j - 1], wholearray[i][j], color2);
			}
		}
	}

}

void RenderTests::BTransTriangles162Test(Drawable * drawable, int xstart, int ystart) {
	const int numbereachrow = 10;
	std::vector<OctantWiz::Point> rowpoints(numbereachrow);
	std::vector<std::vector<OctantWiz::Point>> wholearray;
	OctantWiz::Point first(xstart + 40, ystart + 40);
	int tempY = first.y;
	int translate;
	int upper = 12;
	int lower = -12;

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			rowpoints[j] = OctantWiz::Point(first.x + 25 * j, tempY);
		}
		tempY = tempY + 25;
		wholearray.push_back(rowpoints);
	}

	//translate by [-12, 12]
	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			translate = rand() % ((upper - lower) + 1) + lower;
			wholearray[i][j].x = wholearray[i][j].x + translate;
			wholearray[i][j].y = wholearray[i][j].y + translate;
		}
	}

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			unsigned int color = MathWiz::RandomRGBHex();
			unsigned int color2 = MathWiz::RandomRGBHex();
			if (j > 0) {
				LineRenderer::DDArender(drawable, wholearray[i][j - 1].x, wholearray[i][j - 1].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0) {
				LineRenderer::DDArender(drawable, wholearray[i - 1][j].x, wholearray[i - 1][j].y, wholearray[i][j].x, wholearray[i][j].y, color);
			}
			if (i > 0 && j > 0) {
				PolyFill::BTriangle(drawable, wholearray[i][j], wholearray[i - 1][j], wholearray[i - 1][j - 1], color);
				PolyFill::BTriangle(drawable, wholearray[i][j - 1], wholearray[i - 1][j - 1], wholearray[i][j], color2);
			}
		}
	}
}

void RenderTests::BRandomPolyTest(Drawable * drawable, int x, int y, unsigned int numberofpoly) {
	const unsigned int numberoftri = numberofpoly;
	const unsigned int lowerboundary = 0;
	const unsigned int upperboundary = 300;
	OctantWiz::Point point1();
	OctantWiz::Point point2();
	OctantWiz::Point point3();

	std::vector<unsigned int> xcoord(numberoftri), ycoord(numberoftri);
	std::vector<unsigned int> xendcoord(numberoftri), yendcoord(numberoftri);
	std::vector<unsigned int> xendcoord2(numberoftri), yendcoord2(numberoftri);

	for (int i = 0; i < numberoftri; i++) {
		xcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		ycoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		xendcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		yendcoord[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		xendcoord2[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
		yendcoord2[i] = MathWiz::RandomCoordinate(lowerboundary, upperboundary);
	}

	for (int i = 0; i < numberoftri; i++) {
		PolyFill::BTriangle(drawable, OctantWiz::Point(xcoord[i] + x, ycoord[i] + y), OctantWiz::Point(xendcoord[i] + x, yendcoord[i] + y), OctantWiz::Point(xendcoord2[i] + x, yendcoord2[i] + y), MathWiz::RandomRGBHex());
	}
}

void RenderTests::TransWireframeTri162Test(Drawable * drawable, int xstart, int ystart) {
	const int numbereachrow = 10;
	std::vector<OctantWiz::Point> rowpoints(numbereachrow);
	std::vector<std::vector<OctantWiz::Point>> wholearray;
	OctantWiz::Point first(xstart + 40, ystart + 40);
	int tempY = first.y;
	int translate;
	int upper = 12;
	int lower = -12;

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			rowpoints[j] = OctantWiz::Point(first.x + 60 * j, tempY);
		}
		tempY = tempY + 60;
		wholearray.push_back(rowpoints);
	}

	//translate by [-12, 12]
	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			translate = rand() % ((upper - lower) + 1) + lower;
			wholearray[i][j].x = wholearray[i][j].x + translate;
			wholearray[i][j].y = wholearray[i][j].y + translate;
		}
	}

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			unsigned int color = MathWiz::RandomRGBHex();
			unsigned int color2 = MathWiz::RandomRGBHex();
			unsigned int color3 = MathWiz::RandomRGBHex();
			unsigned int color4 = MathWiz::RandomRGBHex();
			if (j > 0) {
				LineRenderer::LiDDArender(drawable, wholearray[i][j - 1].x, wholearray[i][j - 1].y, wholearray[i][j].x, wholearray[i][j].y, color, color2);
			}
			if (i > 0) {
				LineRenderer::LiDDArender(drawable, wholearray[i - 1][j].x, wholearray[i - 1][j].y, wholearray[i][j].x, wholearray[i][j].y, color3, color4);
			}
		}
	}
}

void RenderTests::TransMeshTri162Test(Drawable * drawable, int xstart, int ystart) {
	const int numbereachrow = 10;
	std::vector<OctantWiz::Point> rowpoints(numbereachrow);
	std::vector<std::vector<OctantWiz::Point>> wholearray;
	OctantWiz::Point first(xstart + 40, ystart + 40);
	int tempY = first.y;
	int translate;
	int upper = 12;
	int lower = -12;

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			rowpoints[j] = OctantWiz::Point(first.x + 60 * j, tempY);
		}
		tempY = tempY + 60;
		wholearray.push_back(rowpoints);
	}

	//translate by [-12, 12]
	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			translate = rand() % ((upper - lower) + 1) + lower;
			wholearray[i][j].x = wholearray[i][j].x + translate;
			wholearray[i][j].y = wholearray[i][j].y + translate;
		}
	}

	for (int i = 0; i < numbereachrow; i++) {
		for (int j = 0; j < numbereachrow; j++) {
			unsigned int color = MathWiz::RandomRGBHex();
			unsigned int color2 = MathWiz::RandomRGBHex();
			unsigned int color3 = MathWiz::RandomRGBHex();
			unsigned int color4 = MathWiz::RandomRGBHex();
			if (j > 0) {
				LineRenderer::LiDDArender(drawable, wholearray[i][j - 1].x, wholearray[i][j - 1].y, wholearray[i][j].x, wholearray[i][j].y, color, color2);
			}
			if (i > 0) {
				LineRenderer::LiDDArender(drawable, wholearray[i - 1][j].x, wholearray[i - 1][j].y, wholearray[i][j].x, wholearray[i][j].y, color3, color4);
			}
			if (i > 0 && j > 0) {
				PolyFill::RealLiTriangle(drawable, wholearray[i][j], wholearray[i - 1][j], wholearray[i - 1][j - 1],
					drawable->getPixel(wholearray[i][j].x, wholearray[i][j].y), drawable->getPixel(wholearray[i - 1][j].x, wholearray[i - 1][j].y), 
					drawable->getPixel(wholearray[i - 1][j - 1].x, wholearray[i - 1][j - 1].y));

				PolyFill::RealLiTriangle(drawable, wholearray[i][j - 1], wholearray[i - 1][j - 1], wholearray[i][j], 
					drawable->getPixel(wholearray[i][j - 1].x, wholearray[i][j - 1].y), drawable->getPixel(wholearray[i - 1][j - 1].x, wholearray[i - 1][j - 1].y), 
					drawable->getPixel(wholearray[i][j].x, wholearray[i][j].y));
			}
		}
	}
}

void RenderTests::zBufferTest(Drawable * drawable) {
	Matrix* zBuffer = new Matrix(650, 650, MType::BACK_PLANE);

	double base_angle = 240;
	double sub_angle = 300;
	double newbase, newsub;
	unsigned int color;
	std::vector<OctantWiz::Point3D> colors;

	colors.push_back(OctantWiz::Point3D(1, 1, 1));
	colors.push_back(OctantWiz::Point3D(0.85, 0.85, 0.85));
	colors.push_back(OctantWiz::Point3D(0.7, 0.7, 0.7));
	colors.push_back(OctantWiz::Point3D(0.55, 0.55, 0.55));
	colors.push_back(OctantWiz::Point3D(0.4, 0.4, 0.4));
	colors.push_back(OctantWiz::Point3D(0.25, 0.25, 0.25));

	for (int i = 0; i < 6; i++) {
		color = MathWiz::getCorrespondingColor(colors[i]);
		int rotation = rand() % 241 - 120;
		newbase = (base_angle + rotation) * M_PI / 180;
		if (rotation > 60) {
			newsub = (sub_angle + rotation - 360) * M_PI / 180;
		}
		else {
			newsub = (sub_angle + rotation) * M_PI / 180;
		}

		OctantWiz::Point point1 = MathWiz::DetermineEndPoint(newbase, 275, 325, 325);
		OctantWiz::Point point2 = MathWiz::DetermineEndPoint(newsub, 275, 325, 325);

		int z1 = rand() % 199 + 1;
		int z2 = rand() % 199 + 1;
		int z3 = rand() % 199 + 1;

		OctantWiz::Point3D origin(325, 325, z1);
		OctantWiz::Point3D endpoint1(point1.x, point1.y, z2);
		OctantWiz::Point3D endpoint2(point2.x, point2.y, z3);

		PolyFill::Triangle3D(drawable, origin, endpoint1, endpoint2, *zBuffer, color, color, color);
	}

	delete zBuffer;
}
