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
	double x = round(matrix->at(0, 0));
	double y = round(matrix->at(1, 0));
	double z = round(matrix->at(2, 0));

	OctantWiz::Point3D result(x, y, z);
	return result;
}

OctantWiz::Point3D MathWiz::NoRoundMatrixToPoint(Matrix * matrix) {
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

Matrix * MathWiz::InverseCTM(Matrix * CTM) {
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result->setAt(i, j, CTM->at(j, i));
		}
	}
	double Uvector[3] = { result->at(0, 0), result->at(0, 1), result->at(0, 2) };
	double Vvector[3] = { result->at(1, 0), result->at(1, 1), result->at(1, 2) };
	double Wvector[3] = { result->at(2, 0), result->at(2, 1), result->at(2, 2) };
	double Tvector[3] = { CTM->at(0, 3), CTM->at(1, 3), CTM->at(2, 3) };

	result->setAt(0, 3, -1 * DotProduct3D(Uvector, Tvector));
	result->setAt(1, 3, -1 * DotProduct3D(Vvector, Tvector));
	result->setAt(2, 3, -1 * DotProduct3D(Wvector, Tvector));
	result->setAt(3, 3, 1);

	return result;
}

OctantWiz::Point3D MathWiz::ProjectPointToZ(OctantWiz::Point3D point) {
	OctantWiz::Point3D result;
	result.x = point.x / point.z;
	result.y = point.y / point.z;
	result.z = point.z;

	return result;
}

Matrix * MathWiz::ProjectVectorToZ(Matrix * vector) {
	Matrix* result = new Matrix(4, 1, MType::ZERO);
	result->setAt(0, 0, vector->at(0, 0) / vector->at(2, 0));
	result->setAt(1, 0, vector->at(1, 0) / vector->at(2, 0));
	result->setAt(2, 0, vector->at(2, 0));
	result->setAt(3, 0, 1);
	MathWiz::debugMatrix(result);
	return result;
}

double MathWiz::DotProduct3D(double vector[3], double Tvector[3]) {
	double result = 0.f;
	for (int i = 0; i < 3; i++) {
		result = result + (vector[i] * Tvector[i]);
	}
	return result;
}

Matrix* MathWiz::makeXRotation(double degrees) {
	double angle = degrees * M_PI / 180;
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, 1);
	result->setAt(1, 1, cos(angle));
	result->setAt(1, 2, sin(angle));
	result->setAt(2, 1, -sin(angle));
	result->setAt(2, 2, cos(angle));
	result->setAt(3, 3, 1);

	return result;
}

Matrix* MathWiz::makeYRotation(double degrees) {
	double angle = degrees * M_PI / 180;
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, cos(angle));
	result->setAt(0, 2, -sin(angle));
	result->setAt(1, 1, 1);
	result->setAt(2, 0, sin(angle));
	result->setAt(2, 2, cos(angle));
	result->setAt(3, 3, 1);

	return result;
}

Matrix* MathWiz::makeZRotation(double degrees) {
	double angle = degrees * M_PI / 180;
	Matrix* result = new Matrix(4, 4, MType::ZERO);

	result->setAt(0, 0, cos(angle));
	result->setAt(0, 1, sin(angle));
	result->setAt(1, 0, -sin(angle));
	result->setAt(1, 1, cos(angle));
	result->setAt(2, 2, 1);
	result->setAt(3, 3, 1);

	return result;
}

void MathWiz::translateToWindowSpace(OctantWiz::Point3D & point) {
	point.x = (point.x + 100) * 3.25;
	point.y = (point.y - 100) * -3.25;
}

unsigned int MathWiz::getCorrespondingColor(OctantWiz::Point3D point) {
	point.x = point.x * 255;
	point.y = point.y * 255;
	point.z = point.z * 255;

	Color colour(point);
	return colour.getHex();
}

OctantWiz::Point3D MathWiz::LightingCalculation(OctantWiz::Point3D ambient, OctantWiz::Point3D surface) {
	OctantWiz::Point3D result;
	result.x = ambient.x * surface.x;
	result.y = ambient.y * surface.y;
	result.z = ambient.z * surface.z;
	return result;
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

void MathWiz::debugMatrix(Matrix * matrix) {
	double list[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			list[i * 4 + j] = matrix->at(i, j);
		}
	}
	int something = 3 + 4;
	int something2 = something + 5;
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


