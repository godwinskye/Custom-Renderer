#include "InterpolatedPolyFill.h"
#include "InterpolatedLines.h"

void PolyFill::WireTriangle3D(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2, Matrix & zBuffer, unsigned int color1, unsigned int color2, unsigned int color3) {
	LineRenderer::LiDDArender3D(drawable, origin, endpoint1, zBuffer, color1, color2);
	LineRenderer::LiDDArender3D(drawable, origin, endpoint2, zBuffer, color1, color3);
	LineRenderer::LiDDArender3D(drawable, endpoint1, endpoint2, zBuffer, color2, color3);
}

void PolyFill::LiTriangle(Drawable * drawable, OctantWiz::Point origin, OctantWiz::Point endpoint1, OctantWiz::Point endpoint2, unsigned int color1, unsigned int color2, unsigned int color3) {
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

	//Initialization of variables
	double leftpoint, rightpoint;
	double lgradient, rgradient;
	Color leftcolor, rightcolor;
	Color leftcolorgradient, rightcolorgradient;

	//Assignment of variables
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

		//Color interpolation for left
		int range = middle.y - top.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
		leftcolor = Color(color1);
		leftcolor.AddColor(leftcolorgradient);

		//Color interpolation for right
		range = bottom.y - top.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color3), range);
		rightcolor = Color(color1);
		rightcolor.AddColor(rightcolorgradient);

		if (leftpoint > rightpoint) {			//swap
			double temp = leftpoint;
			leftpoint = rightpoint;
			rightpoint = temp;
			temp = lgradient;
			lgradient = rgradient;
			rgradient = temp;
			leftIsVar = false;

			Color temp1 = leftcolor;
			leftcolor = rightcolor;
			rightcolor = temp1;

			temp1 = leftcolorgradient;
			leftcolorgradient = rightcolorgradient;
			rightcolorgradient = temp1;
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

		//Color interpolation for left
		int range = middle.y - top.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
		leftcolor = Color(color1);
		leftcolor.AddColor(leftcolorgradient);

		//Color interpolation for right
		range = bottom.y - top.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color3), range);
		rightcolor = Color(color1);
		rightcolor.AddColor(rightcolorgradient);

		if (leftpoint > rightpoint) {			//swap
			double temp = leftpoint;
			leftpoint = rightpoint;
			rightpoint = temp;
			temp = lgradient;
			lgradient = rgradient;
			rgradient = temp;
			leftIsVar = false;

			Color temp1 = leftcolor;
			leftcolor = rightcolor;
			rightcolor = temp1;

			temp1 = leftcolorgradient;
			leftcolorgradient = rightcolorgradient;
			rightcolorgradient = temp1;
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

		//Color interpolation for left
		int range = bottom.y - top.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color3), range);
		leftcolor = Color(color1);
		leftcolor.AddColor(leftcolorgradient);

		//Color interpolation for right
		range = middle.y - top.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
		rightcolor = Color(color1);
		rightcolor.AddColor(rightcolorgradient);
	}

	Color color = leftcolor;
	double redgr, greengr, bluegr;

	int innerRange = rightpoint - leftpoint;

	Color colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);

	for (int y = top.y + 1; y < middle.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			drawable->setPixel(x, y, color.getHex());
			color.AddColor(colorgradient);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;

		leftcolor.AddColor(leftcolorgradient);
		rightcolor.AddColor(rightcolorgradient);

		innerRange = rightpoint - leftpoint;
		colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);
		color = leftcolor;
	}



	if (leftIsVar) {
		lgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			lgradient = 0;
		}
		leftpoint = middle.x;
		leftcolor = color2;
		int range = bottom.y - middle.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color2), Color(color3), range);
	}
	else {
		rgradient = MathWiz::GetReverseGradient(middle, bottom);
		if (middle.x == bottom.x) {
			rgradient = 0;
		}
		rightpoint = middle.x;
		rightcolor = color2;
		int range = bottom.y - middle.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color2), Color(color3), range);
	}

	innerRange = rightpoint - leftpoint;
	colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);

	for (int y = middle.y; y < bottom.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			drawable->setPixel(x, y, color.getHex());
			color.AddColor(colorgradient);
		}
		leftpoint += lgradient;
		rightpoint += rgradient;

		leftcolor.AddColor(leftcolorgradient);
		rightcolor.AddColor(rightcolorgradient);

		innerRange = rightpoint - leftpoint;
		colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);
		color = leftcolor;
	}
}

void PolyFill::Triangle3D(Drawable * drawable, OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2, Matrix & zBuffer, unsigned int color1, unsigned int color2, unsigned int color3) {
	std::vector<OctantWiz::Point3D> list;
	OctantWiz::Point3D top, middle, bottom;
	list.push_back(origin);
	list.push_back(endpoint1);
	list.push_back(endpoint2);
	bool leftIsVar = false;

	PrePolySort3D(list);

	bottom = MathWiz::GetLargestYAndRemoveIt3D(list);
	middle = MathWiz::GetLargestYAndRemoveIt3D(list);
	top = MathWiz::GetLargestYAndRemoveIt3D(list);

	if (top.y == middle.y) {
		if (top.x > middle.x) {
			OctantWiz::Point3D temp = top;
			top = middle;
			middle = temp;
		}
		else if (middle.x <= bottom.x) {
			OctantWiz::Point3D temp = top;
			top = middle;
			middle = temp;
		}
	}

	double gradient = MathWiz::GetReverseGradient3D(top, middle);
	double fgradient = MathWiz::GetReverseGradient3D(top, bottom);
	double zgradient = MathWiz::GetZGradient(top, middle);
	double fzgradient = MathWiz::GetZGradient(top, bottom);

	//Initialization of variables
	double leftpoint, rightpoint;
	double leftzpoint, rightzpoint;
	double lgradient, rgradient;
	double lzgradient, rzgradient;
	Color leftcolor, rightcolor;
	Color leftcolorgradient, rightcolorgradient;

	//Assignment of variables
	if (middle.x < bottom.x) {
		leftpoint = top.x + gradient;
		rightpoint = top.x + fgradient;
		leftzpoint = top.z + zgradient;
		rightzpoint = top.z + fzgradient;

		lgradient = gradient;
		rgradient = fgradient;
		lzgradient = zgradient;
		rzgradient = fzgradient;

		if (top.x == middle.x) {
			lgradient = 0;
		}
		else if (top.x == bottom.x) {
			rgradient = 0;
		}
		leftIsVar = true;

		//Color interpolation for left
		int range = middle.y - top.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
		leftcolor = Color(color1);
		leftcolor.AddColor(leftcolorgradient);

		//Color interpolation for right
		range = bottom.y - top.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color3), range);
		rightcolor = Color(color1);
		rightcolor.AddColor(rightcolorgradient);

		if (leftpoint > rightpoint) {			//swap
			double temp = leftpoint;
			leftpoint = rightpoint;
			rightpoint = temp;
			temp = leftzpoint;
			leftzpoint = rightzpoint;
			rightzpoint = temp;

			temp = lgradient;
			lgradient = rgradient;
			rgradient = temp;
			leftIsVar = false;
			temp = lzgradient;
			lzgradient = rzgradient;
			rzgradient = temp;

			Color temp1 = leftcolor;
			leftcolor = rightcolor;
			rightcolor = temp1;

			temp1 = leftcolorgradient;
			leftcolorgradient = rightcolorgradient;
			rightcolorgradient = temp1;
		}
	}
	else if (middle.x == bottom.x) {
		leftpoint = top.x + gradient;
		rightpoint = top.x + fgradient;
		leftzpoint = top.z + zgradient;
		rightzpoint = top.z + fzgradient;

		lgradient = gradient;
		rgradient = fgradient;
		lzgradient = zgradient;
		rzgradient = fzgradient;

		if (top.x == middle.x) {
			lgradient = 0;
		}
		else if (top.x == bottom.x) {
			rgradient = 0;
		}
		leftIsVar = true;

		//Color interpolation for left
		int range = middle.y - top.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
		leftcolor = Color(color1);
		leftcolor.AddColor(leftcolorgradient);

		//Color interpolation for right
		range = bottom.y - top.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color3), range);
		rightcolor = Color(color1);
		rightcolor.AddColor(rightcolorgradient);

		if (leftpoint > rightpoint) {			//swap
			double temp = leftpoint;
			leftpoint = rightpoint;
			rightpoint = temp;
			temp = lgradient;								
			lgradient = rgradient;
			rgradient = temp;

			temp = leftzpoint;
			leftzpoint = rightzpoint;
			rightzpoint = temp;
			temp = lzgradient;
			lzgradient = rzgradient;
			rzgradient = temp;

			leftIsVar = false;

			Color temp1 = leftcolor;
			leftcolor = rightcolor;
			rightcolor = temp1;

			temp1 = leftcolorgradient;
			leftcolorgradient = rightcolorgradient;
			rightcolorgradient = temp1;
		}
	}
	else {
		leftpoint = top.x + fgradient;
		rightpoint = top.x + gradient;
		leftzpoint = top.z + fzgradient;
		rightzpoint = top.z + zgradient;

		lgradient = fgradient;
		rgradient = gradient;
		lzgradient = fzgradient;
		rzgradient = zgradient;

		if (top.x == middle.x) {
			rgradient = 0;
		}
		else if (top.x == bottom.x) {
			lgradient = 0;
		}
		leftIsVar = false;

		//Color interpolation for left
		int range = bottom.y - top.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color3), range);
		leftcolor = Color(color1);
		leftcolor.AddColor(leftcolorgradient);

		//Color interpolation for right
		range = middle.y - top.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color1), Color(color2), range);
		rightcolor = Color(color1);
		rightcolor.AddColor(rightcolorgradient);
	}

	Color color = leftcolor;
	double redgr, greengr, bluegr;

	int innerRange = rightpoint - leftpoint;
	double currentZ = leftzpoint;
	double innerZgradient = (rightzpoint - leftzpoint) / innerRange;

	Color colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);

	for (int y = top.y + 1; y < middle.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			if (currentZ < zBuffer.at(x, y)) {
				drawable->setPixel(x, y, color.getHex());
			}
			color.AddColor(colorgradient);
			currentZ += innerZgradient;
		}
		leftpoint += lgradient;
		rightpoint += rgradient;
		leftzpoint += lzgradient;
		rightzpoint += rzgradient;

		leftcolor.AddColor(leftcolorgradient);
		rightcolor.AddColor(rightcolorgradient);

		innerRange = rightpoint - leftpoint;
		colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);
		innerZgradient = (rightzpoint - leftzpoint) / innerRange;
		currentZ = leftzpoint;
		color = leftcolor;
	}


	if (leftIsVar) {
		lgradient = MathWiz::GetReverseGradient3D(middle, bottom);
		lzgradient = MathWiz::GetZGradient(middle, bottom);

		if (middle.x == bottom.x) {
			lgradient = 0;
		}

		leftpoint = middle.x;
		leftcolor = color2;
		int range = bottom.y - middle.y;

		leftcolorgradient = MathWiz::GradientOfColors(Color(color2), Color(color3), range);
	}
	else {
		rgradient = MathWiz::GetReverseGradient3D(middle, bottom);
		rzgradient = MathWiz::GetZGradient(middle, bottom);

		if (middle.x == bottom.x) {
			rgradient = 0;
		}

		rightpoint = middle.x;
		rightcolor = color2;
		int range = bottom.y - middle.y;

		rightcolorgradient = MathWiz::GradientOfColors(Color(color2), Color(color3), range);
	}

	innerRange = rightpoint - leftpoint;
	innerZgradient = (rightzpoint - leftzpoint) / innerRange;
	colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);

	for (int y = middle.y; y < bottom.y; y++) {
		for (int x = leftpoint; x <= rightpoint - 1; x++) {
			if (currentZ < zBuffer.at(x, y)) {
				drawable->setPixel(x, y, color.getHex());
			}
			color.AddColor(colorgradient);
			currentZ += innerZgradient;
		}
		leftpoint += lgradient;
		rightpoint += rgradient;
		leftzpoint += lzgradient;
		rightzpoint += rzgradient;

		leftcolor.AddColor(leftcolorgradient);
		rightcolor.AddColor(rightcolorgradient);

		innerRange = rightpoint - leftpoint;
		colorgradient = MathWiz::GradientOfColors(leftcolor, rightcolor, innerRange);
		innerZgradient = (rightzpoint - leftzpoint) / innerRange;
		currentZ = leftzpoint;
		color = leftcolor;
	}
}
