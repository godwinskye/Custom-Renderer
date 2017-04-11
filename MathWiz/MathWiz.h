#pragma once
#define _USE_MATH_DEFINES
#include "../OctantWiz/OctantWiz.h"
#include "../Matrix/Matrix.h"
#include "../Color/Color.h"
#include <math.h>
#include <string>
#include <vector>

namespace MathWiz {

	enum class Quadrant {
		Quadrant1,
		Quadrant2,
		Quadrant3,
		Quadrant4
	};

	Matrix* PointToMatrix(OctantWiz::Point3D point);
	OctantWiz::Point3D MatrixToPoint(Matrix* matrix);

	Matrix* initZBuffer();
	Matrix* matrixMultiplication(Matrix* matrix1, Matrix* matrix2);
	Matrix* makeTranslationMatrix(double tx, double ty, double tz);
	Matrix* makeScaleFactorMatrix(double sx, double sy, double sz);
	Matrix* makeRotationMatrix(Axis type, double degrees);
	Matrix* InverseCTM(Matrix* CTM);
	OctantWiz::Point3D ProjectPointToZ(OctantWiz::Point3D point);
	double DotProduct3D(double vector[3], double Tvector[3]);

	//Rotation types
	Matrix* makeXRotation(double degrees);
	Matrix* makeYRotation(double degrees);
	Matrix* makeZRotation(double degrees);

	//Final translate
	void translateToWindowSpace(OctantWiz::Point3D& point);
	
	//Color swapper
	unsigned int getCorrespondingColor(OctantWiz::Point3D point);

	//Color Interpolation
	Color GradientOfColors(Color origin, Color destination, int range);

	//PolyFill method
	OctantWiz::Point GetLargestYAndRemoveIt(std::vector<OctantWiz::Point>& list);
	OctantWiz::Point3D GetLargestYAndRemoveIt3D(std::vector<OctantWiz::Point3D>& list);

	//Debug routine
	void debugMatrix(Matrix* matrix);

	double GetGradient(OctantWiz::Point origin, OctantWiz::Point endpoint);
	double GetReverseGradient(OctantWiz::Point origin, OctantWiz::Point endpoint);
	double GetReverseGradient3D(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint);
	double GetZGradient(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint);
	double GetGradient3D(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint);
	double GetGradientS(OctantWiz::SPoint point1, OctantWiz::SPoint point2);
	OctantWiz::Point DetermineEndPoint(double currentangle, int length, int x, int y);
	Quadrant DetermineQuadrant(double angle);
	unsigned int RandomCoordinate(unsigned int lower, unsigned int upper);
	unsigned int RandomRGBHex();
	double PointDistance(OctantWiz::Point origin, OctantWiz::Point endpoint);
	double LargestOfThree(double first, double second, double third);
	double FindLongestLength(OctantWiz::SPoint origin, OctantWiz::SPoint endpoint);
}