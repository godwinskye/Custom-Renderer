#include "PolyFill.h"
#include "LineRender.h"

#define ALTER

void PolyFill::Triangle(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color) {
	std::vector<OctantWiz::Point> list;
	OctantWiz::Point top, middle, bottom;
	list.push_back(origin);
	list.push_back(endpoint1);
	list.push_back(endpoint2);
	bool leftIsVar = false;

	PrePolySort(list);

	bottom = MathWiz::GetLargestYAndRemoveIt(list);
	middle = MathWiz::GetLargestYAndRemoveIt(list);
	top = MathWiz::GetLargestYAndRemoveIt(list);

	if (top.y == middle.y) {
		if (top.x > middle.x) {
			OctantWiz::Point temp = top;
			top = middle;
			middle = temp;
		}
		else if (middle.x <= bottom.x) {
			OctantWiz::Point temp = top;
			top = middle;
			middle = temp;
		}
	}

	double gradient = MathWiz::GetReverseGradient(top, middle);
	double fgradient = MathWiz::GetReverseGradient(top, bottom);

	double leftpoint, rightpoint;
	double lgradient, rgradient;

	if (middle.x < bottom.x) {
		leftpoint = top.x + gradient;
		rightpoint = top.x + fgradient;
		lgradient = gradient;
		rgradient = fgradient;
		if (top.x == middle.x) {
			lgradient = 0;
		}
		else if (top.x == bottom.x) {
			rgradient = 0;
		}
		leftIsVar = true;
		if (leftpoint > rightpoint) {			//swap
			double temp = leftpoint;
			leftpoint = rightpoint;
			rightpoint = temp;
			temp = lgradient;
			lgradient = rgradient;
			rgradient = temp;
			leftIsVar = false;
		}
	}
	else if (middle.x == bottom.x) {
		leftpoint = top.x + gradient;
		rightpoint = top.x + fgradient;
		lgradient = gradient;
		rgradient = fgradient;
		if (top.x == middle.x) {
			lgradient = 0;
		}
		else if (top.x == bottom.x) {
			rgradient = 0;
		}
		leftIsVar = true;
		if (leftpoint > rightpoint) {			//swap
			double temp = leftpoint;
			leftpoint = rightpoint;
			rightpoint = temp;
			temp = lgradient;
			lgradient = rgradient;
			rgradient = temp;
			leftIsVar = false;
		}
	}
	else {
		leftpoint = top.x + fgradient;
		rightpoint = top.x + gradient;
		lgradient = fgradient;
		rgradient = gradient;
		if (top.x == middle.x) {
			rgradient = 0;
		}
		else if (top.x == bottom.x) {
			lgradient = 0;
		}
		leftIsVar = false;
	}


	for (int y = top.y + 1; y < middle.y; y++) {
		for (int x = leftpoint; x <= round(rightpoint); x++) {
			drawable->setPixel(x, y, color);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;
	}


	if (leftIsVar) {
		lgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			lgradient = 0;
		}
		if (leftpoint > middle.x) {
			leftpoint = middle.x;
		}
	}
	else {
		rgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			rgradient = 0;
		}
		rightpoint = middle.x;
	}



	for (int y = middle.y; y < bottom.y; y++) {
		for (int x = leftpoint; x <= round(rightpoint); x++) {
			drawable->setPixel(x, y, color);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;
	}
}

void PolyFill::PrePolySort(std::vector<OctantWiz::Point>& list) {
	for (int i = 0; i < list.size(); i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (list[i].x > list[j].x) {
				OctantWiz::Point temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}

void PolyFill::PrePolySort3D(std::vector<OctantWiz::Point3D>& list) {
	for (int i = 0; i < list.size(); i++) {
		for (int j = i + 1; j < list.size(); j++) {
			if (list[i].x > list[j].x) {
				OctantWiz::Point3D temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}
	}
}