#pragma once
#include "OctantWiz/OctantWiz.h"

class Color {
public:
	Color();
	Color(unsigned int hex);
	//X value = Red, Y value = Green, Z value = Blue
	Color(OctantWiz::Point3D point);

	void AddColor(Color othercolor);
	void SubtractColor(Color othercolor);
	void DivideScalar(int scalar);

	unsigned int getHex();

private:
	double red = 0;
	double green = 0;
	double blue = 0;
};