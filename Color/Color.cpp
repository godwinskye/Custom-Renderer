#include "Color.h"

Color::Color() {
	red = 0.f;
	green = 0.f;
	blue = 0.f;
}

Color::Color(unsigned int hex) {
	red = ((hex >> 16) & 0xff);
	green = ((hex >> 8) & 0xff);
	blue = (hex & 0xff);
}

void Color::AddColor(Color othercolor) {
	red = red + othercolor.red;
	green = green + othercolor.green;
	blue = blue + othercolor.blue;
}

void Color::SubtractColor(Color othercolor) {
	red = red - othercolor.red;
	green = green - othercolor.green;
	blue = blue - othercolor.blue;
}

void Color::DivideScalar(int scalar) {
	red = red / scalar;
	green = green / scalar;
	blue = blue / scalar;
}

unsigned int Color::getHex() {
	int tempred = static_cast<int>(red);
	int tempgreen = static_cast<int>(green);
	int tempblue = static_cast<int>(blue);

	unsigned int color = (0xff << 24) + ((tempred & 0xff) << 16) + ((tempgreen & 0xff) << 8) + (tempblue & 0xff);

	return color;
}
