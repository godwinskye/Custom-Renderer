#include "MathWiz.h"

double MathWiz::GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	return (double)(endpoint.y - origin.y) / (double)(endpoint.x - origin.x);
}
