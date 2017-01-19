#include "MathWiz.h"
#include <math.h>

double MathWiz::GetGradient(int x1, int y1, int x2, int y2) {
	return (y2 - y1) / (x2 - x1);
}
