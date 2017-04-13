#pragma once
#include <string>
#include <fstream>
#include <stack>
#include "Camera/Camera.h"
#include "renderarea361.h"
#include "MathWiz/MathWiz.h"

class Interpreter {
public:
	Interpreter(Drawable *drawable, std::string filename);
	Interpreter(Drawable *drawable, std::string filename, OctantWiz::Point3D lighter, OctantWiz::Point3D darker);

	void interpretStream(std::ifstream &stream);
	void interpretLine(std::string line);

	std::string appendSubsequentAlphabets(std::string line, int &position);
	double grabNextNum(std::string line, int &position);
	void fitToken(std::string token, std::string line, int &position);
	std::string getFilename(std::string line, int &position);

	void ScaleCTM(double sx, double sy, double sz);
	void TranslateCTM(double tx, double ty, double tz);
	void RotateCTM(Axis axis, double degrees);
	void RenderPolygon(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2);
	void RenderLine(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint);

	OctantWiz::Point3D obtainColor(double zvalue);
	unsigned int getColor(OctantWiz::Point3D point);

	//Camera tools
	void SetCamera(double xlow, double ylow, double xhigh, double yhigh, double hither, double yon);

	std::ifstream mainfile;
private:
	double scale = 3.25;
	double zBufferMaxDistance = 200.f;
	double zBufferMin = 0.f;

	OctantWiz::Point3D near = OctantWiz::Point3D(0, 1, 0);
	OctantWiz::Point3D far = OctantWiz::Point3D(0, 0, 0);

	OctantWiz::Point3D Ambient = OctantWiz::Point3D(0, 0, 0);
	OctantWiz::Point3D Surface = OctantWiz::Point3D(1, 1, 1);

	double DepthNear = DBL_MAX;
	double DepthFar = DBL_MAX;
	OctantWiz::Point3D DepthColor;
	Color DepthColorGradient;

	std::stack<Matrix*> CTMstack;
	Matrix zBuffer = Matrix(1000, 1000, MType::BACK_PLANE);
	Matrix* CTM = new Matrix(4, 4, MType::IDENTITY);
	Camera CameraSpace;
	bool CameraSwitch = false;
	bool DepthSwitch = false;
	bool FILLED = true;
	Drawable* draw;

	int polygon = 0;
};