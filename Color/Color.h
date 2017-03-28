#pragma once

class Color {
public:
	Color();
	Color(unsigned int hex);

	void AddColor(Color othercolor);
	void SubtractColor(Color othercolor);
	void DivideScalar(int scalar);

	unsigned int getHex();

private:
	double red = 0;
	double green = 0;
	double blue = 0;
};