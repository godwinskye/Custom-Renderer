#include "MathWiz.h"
#include <stdlib.h>

//to only calculate this once
static double thirdquad = M_PI + M_PI_2;

Matrix* MathWiz::PointToMatrix(OctantWiz::Point3D point) {
	Matrix* result = new Matrix(4, 1, MType::ZERO);
	
	result->setAt(0, 0, point.x);
	result->setAt(1, 0, point.y);
	result->setAt(2, 0, point.z);
	result->setAt(3, 0, 1);

	return result;
}

OctantWiz::Point3D MathWiz::MatrixToPoint(Matrix* matrix) {
	double x = matrix->at(0, 0);
	double y = matrix->at(1, 0);
	double z = matrix->at(2, 0);

	OctantWiz::Point3D result(x, y, z);
	return result;
}

Matrix* MathWiz::initZBuffer() {
	Matrix* buffer = new Matrix(650, 650, MType::BACK_PLANE);
	return buffer;
}

Matrix* MathWiz::matrixMultiplication(Matrix* matrix1, Matrix* matrix2) {
	double temp = 0;
	int row = matrix1->getRow();
	int column = matrix2->getWidth();
	Matrix* result = new Matrix(row, column, MType::ZERO);

	for (int row = 0; row < matrix1->getRow(); row++) {
		for (int col = 0; col < matrix2->getWidth(); col++) {
			for (int m2row = 0; m2row < matrix2->getRow(); m2row++) {
				temp = temp + matrix1->at(row, m2row) * matrix2->at(m2row, col);
			}
			result->setAt(row, col, temp);
			temp = 0;
		}
	}
	return result;
}

Matrix* MathWiz::makeTranslationMatrix(double tx, double ty, double tz) {
	Matrix* result = new Matrix(4, 4, MType::IDENTITY);

	result->setAt(0, 3, tx);
	result->setAt(1, 3, ty);
	result->setAt(2, 3, tz);
	
	return result;
}

Matrix* MathWiz::makeScaleFactorMatrix(double sx, double sy, double sz) {
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, sx);
	result->setAt(1, 1, sy);
	result->setAt(2, 2, sz);
	result->setAt(3, 3, 1);

	return result;
}

Matrix* MathWiz::makeRotationMatrix(Axis type, double degrees) {
	switch (type) {
	case Axis::XAXIS:
		return makeXRotation(degrees);
	case Axis::YAXIS:
		return makeYRotation(degrees);
	case Axis::ZAXIS:
		return makeZRotation(degrees);
	}
}

Matrix* MathWiz::makeXRotation(double degrees) {
	double angle = degrees * M_PI / 180;
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, 1);
	result->setAt(1, 1, cos(angle));
	result->setAt(1, 2, -sin(angle));
	result->setAt(2, 1, sin(angle));
	result->setAt(2, 2, cos(angle));
	result->setAt(3, 3, 1);

	return result;
}

Matrix* MathWiz::makeYRotation(double degrees) {
	double angle = degrees * M_PI / 180;
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, cos(angle));
	result->setAt(0, 2, sin(angle));
	result->setAt(1, 1, 1);
	result->setAt(2, 0, -sin(angle));
	result->setAt(2, 2, cos(angle));
	result->setAt(3, 3, 1);

	return result;
}

Matrix* MathWiz::makeZRotation(double degrees) {
	double angle = degrees * M_PI / 180;
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, cos(angle));
	result->setAt(0, 1, -sin(angle));
	result->setAt(1, 0, sin(angle));
	result->setAt(1, 1, cos(angle));
	result->setAt(2, 2, 1);
	result->setAt(3, 3, 1);

	return result;
}

void MathWiz::translateToWindowSpace(OctantWiz::Point3D & point) {
	point.x = (point.x + 100) * 3.25;
	point.y = (point.y + 100) * 3.25;
}

unsigned int MathWiz::getCorrespondingColor(OctantWiz::Point3D point) {
	unsigned int red = point.x * 255;
	unsigned int green = point.y * 255;
	unsigned int blue = point.z * 255;

	unsigned int colour = (0xff << 24) + ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	return colour;
}

void MathWiz::InterpolateColorOnce(unsigned int& color, double redgradient, double greengradient, double bluegradient) {
	double red = (color >> 16) & 0xff;
	double green = (color >> 8) & 0xff;
	double blue = color & 0xff;

	if (red + redgradient >= 255) {
		red = 255;
	}
	else if (red + redgradient <= 0) {
		red = 0;
	}
	else {
		red = red + redgradient;
	}

	if (green + greengradient >= 255) {
		green = 255;
	}
	else if (green + greengradient <= 0) {
		green = 0;
	}
	else {
		green = green + greengradient;
	}

	if (blue + bluegradient >= 255) {
		blue = 255;
	}
	else if (blue + bluegradient <= 0) {
		blue = 0;
	}
	else {
		blue = blue + bluegradient;
	}

	color = (0xff << 24) + ((static_cast<unsigned int>(round(red)) & 0xff) << 16) + ((static_cast<unsigned int>(round(green)) & 0xff) << 8) + (static_cast<unsigned int>(round(blue)) & 0xff);
}

Color MathWiz::GradientOfColors(Color origin, Color destination, int range) {
	destination.SubtractColor(origin);
	destination.DivideScalar(range);
	return destination;
}

OctantWiz::Point MathWiz::GetLargestYAndRemoveIt(std::vector<OctantWiz::Point>& list) {
	OctantWiz::Point largestpoint = list[0];
	int index = 0;
	for (int i = 0; i < list.size(); i++) {
		if (largestpoint.y <= list[i].y) {
			largestpoint = list[i];
			index = i;
		}
	}
	list.erase(list.begin() + index);
	return largestpoint;
}

OctantWiz::Point3D MathWiz::GetLargestYAndRemoveIt3D(std::vector<OctantWiz::Point3D>& list) {
	OctantWiz::Point3D largestpoint = list[0];
	int index = 0;
	for (int i = 0; i < list.size(); i++) {
		if (largestpoint.y <= list[i].y) {
			largestpoint = list[i];
			index = i;
		}
	}
	list.erase(list.begin() + index);
	return largestpoint;
}

double MathWiz::GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	return static_cast<double>((endpoint.y - origin.y)) / static_cast<double>((endpoint.x - origin.x));
}

double MathWiz::GetReverseGradient(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	if ((endpoint.y - origin.y) == 0) {
		return 0.f;
	}
	return static_cast<double>((endpoint.x - origin.x)) / static_cast<double>((endpoint.y - origin.y));
}

double MathWiz::GetReverseGradient3D(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint) {
	if ((endpoint.y - origin.y) == 0) {
		return 0.f;
	}
	return static_cast<double>((endpoint.x - origin.x)) / static_cast<double>((endpoint.y - origin.y));
}

double MathWiz::GetZGradient(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint) {
	if ((endpoint.y - origin.y) == 0) {
		return 0.f;
	}
	return static_cast<double>((endpoint.z - origin.z)) / static_cast<double>((endpoint.y - origin.y));
}

double MathWiz::GetGradient3D(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint) {
	return static_cast<double>((endpoint.y - origin.y)) / static_cast<double>((endpoint.x - origin.x));
}

double MathWiz::GetGradientS(OctantWiz::SPoint point1, OctantWiz::SPoint point2) {
	return (point2.y - point1.y) / (point2.x - point1.x);
}

OctantWiz::Point MathWiz::DetermineEndPoint(double currentangle, int length, int x, int y) {
	MathWiz::Quadrant quadrant = DetermineQuadrant(currentangle);
	
	switch (quadrant) {
	case MathWiz::Quadrant::Quadrant1: {
		int x_diff = length * cos(currentangle);
		int y_diff = length * sin(currentangle);
		OctantWiz::Point endpoint(x + x_diff, y - y_diff);
		return endpoint;
	}
		break;
	case MathWiz::Quadrant::Quadrant2: {
		int x_diff = length * cos(M_PI - currentangle);
		int y_diff = length * sin(M_PI - currentangle);
		OctantWiz::Point endpoint(x - x_diff, y - y_diff);
		return endpoint;
	}
		break;
	case MathWiz::Quadrant::Quadrant3: {
		int x_diff = length * sin(thirdquad - currentangle);
		int y_diff = length * cos(thirdquad - currentangle);
		OctantWiz::Point endpoint(x - x_diff, y + y_diff);
		return endpoint;
	}
		break;
	case MathWiz::Quadrant::Quadrant4: {
		int x_diff = length * cos(2 * M_PI - currentangle);
		int y_diff = length * sin(2 * M_PI - currentangle);
		OctantWiz::Point endpoint(x + x_diff, y + y_diff);
		return endpoint;
	}
		break;
	}
}

MathWiz::Quadrant MathWiz::DetermineQuadrant(double angle) {
	if (angle <= M_PI_2) {
		return MathWiz::Quadrant::Quadrant1;
	}
	else if (angle > M_PI_2 && angle <= M_PI) {
		return MathWiz::Quadrant::Quadrant2;
	}
	else if (angle > M_PI && angle <= thirdquad) {
		return MathWiz::Quadrant::Quadrant3;
	}
	else {
		return MathWiz::Quadrant::Quadrant4;
	}
}

unsigned int MathWiz::RandomCoordinate(unsigned int lower, unsigned int upper) {
	unsigned int coordinate = rand() % upper + lower;
	return coordinate;
}

unsigned int MathWiz::RandomRGBHex() {
	unsigned int range = 256;
	unsigned int red = rand() % range;
	unsigned int green = rand() % range;
	unsigned int blue = rand() % range;

	unsigned int colour = (0xff << 24) + ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	return colour;
}

double MathWiz::PointDistance(OctantWiz::Point origin, OctantWiz::Point endpoint) {
	double xpart = pow(endpoint.x - origin.x, 2);
	double ypart = pow(endpoint.y - origin.y, 2);
	double distance = sqrt(xpart + ypart);
	return distance;
}

double MathWiz::LargestOfThree(double first, double second, double third) {
	if (first >= second && first >= third) {
		return first;
	}
	else if (second >= first && second >= third) {
		return second;
	}
	else {
		return third;
	}
}

double MathWiz::FindLongestLength(OctantWiz::SPoint origin, OctantWiz::SPoint endpoint) {
	double length1 = abs(endpoint.x - origin.x);
	double length2 = abs(endpoint.y - origin.y);

	if (length1 >= length2) {
		return length1;
	}
	else {
		return length2;
	}
}


