#include "Interpreter.h"
#include "OctantWiz/OctantWiz.h"
#include "Renderer/InterpolatedLines.h"
#include "Renderer/InterpolatedPolyFill.h"
#include <iostream>
#include <cctype>

#define ALTER

Interpreter::Interpreter(Drawable *drawable, std::string filename) {
	filename += ".simp";
	draw = drawable;
	ALTER mainfile.open(filename, std::ifstream::in);
	interpretStream(mainfile);
}

Interpreter::Interpreter(Drawable * drawable, std::string filename, OctantWiz::Point3D close, OctantWiz::Point3D further) {
	filename += ".simp";
	draw = drawable;
	near = close;
	far = further;
	ALTER mainfile.open(filename, std::ifstream::in);
	interpretStream(mainfile);
}

void Interpreter::interpretStream(std::ifstream &stream) {
	std::string line;
	while (stream.good()) {
		std::getline(stream, line);
		interpretLine(line);
	}
}

void Interpreter::interpretLine(std::string line) {
	std::string token;
	//check if comment
	if (line[0] == '#') {
		return;
	}
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t') {
			continue;
		}
		//TODO: Fix shallow push
		else if (line[i] == '{') {
			Matrix* clone = new Matrix(CTM);
			CTMstack.push(clone);
		}
		else if (line[i] == '}') {
			CTM = CTMstack.top();
			CTMstack.pop();
		}
		else {
			token = appendSubsequentAlphabets(line, ALTER i);
			fitToken(token, line, ALTER i);
		}
	}
}

//returns first Keyword with current line[i] at WHITESPACE or NEWLINE
std::string Interpreter::appendSubsequentAlphabets(std::string line, int &position) {
	std::string token;
	token += line[position];
	for (position = position + 1; position < line.length(); position++) {
		if (line[position] == ' ' || line[position] == '\n') {
			break;
		}
		else {
			token += line[position];
		}
	}
	return token;
}

double Interpreter::grabNextNum(std::string line, int & position) {
	std::string number;
	bool start = false;
	bool floating = false;
	for (position; position < line.length(); position++) {
		if (isdigit(line[position]) || line[position] == '-') {
			number += line[position];
			start = true;
		}
		else if (line[position] == '.' && !floating) {
			number += line[position];
			floating = true;
		}
		else {
			if (start) {
				if (floating) {
					return std::stod(number);
				}
				else {
					return static_cast<double>(std::stoi(number));
				}
			}
		}
	}
	if (start) {
		if (floating) {
			return std::stod(number);
		}
		else {
			return static_cast<double>(std::stoi(number));
		}
	}
}

//position at WHITESPACE or NEWLINE
void Interpreter::fitToken(std::string token, std::string line, int &position) {
	if (token == "polygon") {
		double a, b, c;

		a = grabNextNum(line, position);
		b = grabNextNum(line, position);
		c = grabNextNum(line, position);
		OctantWiz::Point3D origin(a, b, c);
		
		a = grabNextNum(line, position);
		b = grabNextNum(line, position);
		c = grabNextNum(line, position);
		OctantWiz::Point3D endpoint1(a, b, c);

		a = grabNextNum(line, position);
		b = grabNextNum(line, position);
		c = grabNextNum(line, position);
		OctantWiz::Point3D endpoint2(a, b, c);

		RenderPolygon(origin, endpoint1, endpoint2);
	}
	else if (token == "line") {
		double a, b, c;

		a = grabNextNum(line, position);
		b = grabNextNum(line, position);
		c = grabNextNum(line, position);
		OctantWiz::Point3D origin(a, b, c);

		a = grabNextNum(line, position);
		b = grabNextNum(line, position);
		c = grabNextNum(line, position);
		OctantWiz::Point3D endpoint(a, b, c);

		RenderLine(origin, endpoint);
	}
	else if (token == "scale") {
		double sx = grabNextNum(line, position);
		double sy = grabNextNum(line, position);
		double sz = grabNextNum(line, position);
		ScaleCTM(sx, sy, sz);
	}
	else if (token == "rotate") {
		position = position + 1;
		char axis = line[position];
		Axis Eaxis;
		switch (axis) {
		case 'X':
			Eaxis = Axis::XAXIS;
			break;
		case 'Y':
			Eaxis = Axis::YAXIS;
			break;
		case 'Z':
			Eaxis = Axis::ZAXIS;
			break;
		}
		double degrees = grabNextNum(line, position);
		RotateCTM(Eaxis, degrees);
	}
	else if (token == "translate") {
		double tx = grabNextNum(line, position);
		double ty = grabNextNum(line, position);
		double tz = grabNextNum(line, position);
		TranslateCTM(tx, ty, tz);
	}
	else if (token == "file") {
		std::ifstream substream;
		std::string filename = getFilename(line, position);
		filename += ".simp";
		ALTER substream.open(filename, std::ifstream::in);
		interpretStream(substream);
	}
	else if (token == "wire") {
		FILLED = false;
	}
	else if (token == "filled") {
		FILLED = true;
	}
	else if (token == "camera") {
		double xlow = grabNextNum(line, position);
		double ylow = grabNextNum(line, position);
		double xhigh = grabNextNum(line, position);
		double yhigh = grabNextNum(line, position);
		double hither = grabNextNum(line, position);
		double yon = grabNextNum(line, position);

		SetCamera(xlow, ylow, xhigh, yhigh, hither, yon);
		CameraSwitch = true;
		zBufferMin = hither;
		zBufferMaxDistance = yon;
	}
	else if (token == "ambient") {
		double red = grabNextNum(line, position);
		double green = grabNextNum(line, position);
		double blue = grabNextNum(line, position);

		Ambient.x = red;
		Ambient.y = green;
		Ambient.z = blue;

		Color nearcolor = MathWiz::getCorrespondingColor(MathWiz::LightingCalculation(Ambient, Surface));
		Color farcolor = MathWiz::getCorrespondingColor(DepthColor);
		DepthColorGradient = MathWiz::GradientOfColors(nearcolor, farcolor, DepthFar - DepthNear);
	}
	else if (token == "surface") {
		double red = grabNextNum(line, position);
		double green = grabNextNum(line, position);
		double blue = grabNextNum(line, position);

		Surface.x = red;
		Surface.y = green;
		Surface.z = blue;

		Color nearcolor = MathWiz::getCorrespondingColor(MathWiz::LightingCalculation(Ambient, Surface));
		Color farcolor = MathWiz::getCorrespondingColor(DepthColor);
		DepthColorGradient = MathWiz::GradientOfColors(nearcolor, farcolor, DepthFar - DepthNear);
	}
	else if (token == "depth") {
		double newnear = grabNextNum(line, position);
		double newfar = grabNextNum(line, position);
		DepthNear = newnear;
		DepthFar = newfar;

		double red = grabNextNum(line, position);
		double green = grabNextNum(line, position);
		double blue = grabNextNum(line, position);

		DepthColor.x = red;
		DepthColor.y = green;
		DepthColor.z = blue;

		//DepthColorGradient setup
		Color nearcolor = MathWiz::getCorrespondingColor(MathWiz::LightingCalculation(Ambient, Surface));
		Color farcolor = MathWiz::getCorrespondingColor(DepthColor);
		DepthColorGradient = MathWiz::GradientOfColors(nearcolor, farcolor, DepthFar - DepthNear);
	}
}

std::string Interpreter::getFilename(std::string line, int & position) {
	std::string filename;
	bool insidestring = false;
	for (position; position < line.length(); position++) {
		if (insidestring && line[position] != '"') {
			filename += line[position];
		}
		if (line[position] == '"' && !insidestring) {
			insidestring = true;
		}
		else if (line[position] == '"' && insidestring) {
			return filename;
		}
	}
}

void Interpreter::ScaleCTM(double sx, double sy, double sz) {
	Matrix* scaler = MathWiz::makeScaleFactorMatrix(sx, sy, sz);
	CTM = MathWiz::matrixMultiplication(CTM, scaler);
	delete scaler;
}

void Interpreter::TranslateCTM(double tx, double ty, double tz) {
	Matrix* translation = MathWiz::makeTranslationMatrix(tx, ty, tz);
	CTM = MathWiz::matrixMultiplication(CTM, translation);
	delete translation;
}

void Interpreter::RotateCTM(Axis axis, double degrees) {
	switch (axis) {
		case Axis::XAXIS: {
			Matrix* rotation = MathWiz::makeXRotation(degrees);
			CTM = MathWiz::matrixMultiplication(CTM, rotation);
			delete rotation;
			break;
		}
		case Axis::YAXIS: {
			Matrix* rotation = MathWiz::makeYRotation(degrees);
			CTM = MathWiz::matrixMultiplication(CTM, rotation);
			delete rotation;
			break;
		}
		case Axis::ZAXIS: {
			Matrix* rotation = MathWiz::makeZRotation(degrees);
			CTM = MathWiz::matrixMultiplication(CTM, rotation);
			delete rotation;
			break;
		}
	}
}

void Interpreter::RenderPolygon(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2) {
	Matrix* origin1 = MathWiz::PointToMatrix(origin);
	
	Matrix* endpoint11 = MathWiz::PointToMatrix(endpoint1);
	Matrix* endpoint22 = MathWiz::PointToMatrix(endpoint2);

	Matrix* torigin = MathWiz::matrixMultiplication(CTM, origin1);
	Matrix* tendpoint1 = MathWiz::matrixMultiplication(CTM, endpoint11);
	Matrix* tendpoint2 = MathWiz::matrixMultiplication(CTM, endpoint22);

	delete origin1;
	delete endpoint11;
	delete endpoint22;

	if (CameraSwitch) {
		torigin = MathWiz::matrixMultiplication(CameraSpace.Space, torigin);
		tendpoint1 = MathWiz::matrixMultiplication(CameraSpace.Space, tendpoint1);
		tendpoint2 = MathWiz::matrixMultiplication(CameraSpace.Space, tendpoint2);

		OctantWiz::Point3D res_origin = MathWiz::NoRoundMatrixToPoint(torigin);
		OctantWiz::Point3D res_endpt1 = MathWiz::NoRoundMatrixToPoint(tendpoint1);
		OctantWiz::Point3D res_endpt2 = MathWiz::NoRoundMatrixToPoint(tendpoint2);

		res_origin = MathWiz::ProjectPointToZ(res_origin);
		res_endpt1 = MathWiz::ProjectPointToZ(res_endpt1);
		res_endpt2 = MathWiz::ProjectPointToZ(res_endpt2);

		torigin = MathWiz::PointToMatrix(res_origin);
		tendpoint1 = MathWiz::PointToMatrix(res_endpt1);
		tendpoint2 = MathWiz::PointToMatrix(res_endpt2);

		double xscale = CameraSpace.Original.xhigh - CameraSpace.Original.xlow;
		double yscale = CameraSpace.Original.yhigh - CameraSpace.Original.ylow;

		Matrix* screenscale = MathWiz::makeScaleFactorMatrix(650 / xscale, -1 * 650 / yscale, 1);
		Matrix* screentranslate = MathWiz::makeTranslationMatrix(325, 325, 0);

		torigin = MathWiz::matrixMultiplication(screenscale, torigin);
		torigin = MathWiz::matrixMultiplication(screentranslate, torigin);

		tendpoint1 = MathWiz::matrixMultiplication(screenscale, tendpoint1);
		tendpoint1 = MathWiz::matrixMultiplication(screentranslate, tendpoint1);

		tendpoint2 = MathWiz::matrixMultiplication(screenscale, tendpoint2);
		tendpoint2 = MathWiz::matrixMultiplication(screentranslate, tendpoint2);

		res_origin = MathWiz::NoRoundMatrixToPoint(torigin);
		res_endpt1 = MathWiz::NoRoundMatrixToPoint(tendpoint1);
		res_endpt2 = MathWiz::NoRoundMatrixToPoint(tendpoint2);

		delete torigin;
		delete tendpoint1;
		delete tendpoint2;

		OctantWiz::Point3D color1, color2, color3;

		if (res_origin.z <= DepthNear) {
			color1 = MathWiz::LightingCalculation(Ambient, Surface);
		}
		else if (res_origin.z >= DepthFar) {
			color1 = DepthColor;
		}
		else {
			Color temp = Color(MathWiz::LightingCalculation(Ambient, Surface));
			temp.AddColorMultiple(DepthColorGradient, (res_origin.z - DepthNear));
			color1 = temp.getPoint3D();
		}

		if (res_endpt1.z <= DepthNear) {
			color2 = MathWiz::LightingCalculation(Ambient, Surface);
		}
		else if (res_endpt1.z >= DepthFar) {
			color1 = DepthColor;
		}
		else {
			Color temp = Color(MathWiz::LightingCalculation(Ambient, Surface));
			temp.AddColorMultiple(DepthColorGradient, (res_endpt1.z - DepthNear));
			color2 = temp.getPoint3D();
		}

		if (res_endpt2.z <= DepthNear) {
			color3 = MathWiz::LightingCalculation(Ambient, Surface);
		}
		else if (res_endpt2.z >= DepthFar) {
			color3 = DepthColor;
		}
		else {
			Color temp = Color(MathWiz::LightingCalculation(Ambient, Surface));
			temp.AddColorMultiple(DepthColorGradient, (res_endpt2.z - DepthNear));
			color3 = temp.getPoint3D();
		}

		unsigned int res_color = getColor(color1);

		if (FILLED) {
			PolyFill::ScissorTriangle3D(draw, res_origin, res_endpt1, res_endpt2, zBuffer, res_color, res_color, res_color, CameraSpace.Frustum);
		}
		else {
			PolyFill::WireTriangle3D(draw, res_origin, res_endpt1, res_endpt2, zBuffer, res_color, res_color, res_color, CameraSpace.Frustum);
		}
	}
	else {
		Matrix* screenscale = MathWiz::makeScaleFactorMatrix(3.25, -3.25, 1);
		Matrix* screentranslate = MathWiz::makeTranslationMatrix(325, 325, 0);

		torigin = MathWiz::matrixMultiplication(screenscale, torigin);
		torigin = MathWiz::matrixMultiplication(screentranslate, torigin);

		tendpoint1 = MathWiz::matrixMultiplication(screenscale, tendpoint1);
		tendpoint1 = MathWiz::matrixMultiplication(screentranslate, tendpoint1);

		tendpoint2 = MathWiz::matrixMultiplication(screenscale, tendpoint2);
		tendpoint2 = MathWiz::matrixMultiplication(screentranslate, tendpoint2);


		OctantWiz::Point3D res_origin = MathWiz::MatrixToPoint(torigin);
		OctantWiz::Point3D res_endpt1 = MathWiz::MatrixToPoint(tendpoint1);
		OctantWiz::Point3D res_endpt2 = MathWiz::MatrixToPoint(tendpoint2);

		delete torigin;
		delete tendpoint1;
		delete tendpoint2;

		OctantWiz::Point3D color1 = obtainColor(res_origin.z);
		OctantWiz::Point3D color2 = obtainColor(res_endpt1.z);
		OctantWiz::Point3D color3 = obtainColor(res_endpt2.z);

		unsigned int res_color1 = getColor(color1);
		unsigned int res_color2 = getColor(color2);
		unsigned int res_color3 = getColor(color3);

		if (FILLED) {
			PolyFill::Triangle3D(draw, res_origin, res_endpt1, res_endpt2, zBuffer, res_color1, res_color2, res_color3);
		}
		else {
			PolyFill::WireTriangle3D(draw, res_origin, res_endpt1, res_endpt2, zBuffer, res_color1, res_color2, res_color3);
		}
	}
}

void Interpreter::RenderLine(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint) {
	Matrix* origin1 = MathWiz::PointToMatrix(origin);
	Matrix* endpoint11 = MathWiz::PointToMatrix(endpoint);

	Matrix* torigin = MathWiz::matrixMultiplication(CTM, origin1);
	Matrix* tendpoint1 = MathWiz::matrixMultiplication(CTM, endpoint11);

	delete origin1;
	delete endpoint11;

	OctantWiz::Point3D res_origin = MathWiz::MatrixToPoint(torigin);
	OctantWiz::Point3D res_endpt = MathWiz::MatrixToPoint(tendpoint1);

	delete torigin;
	delete tendpoint1;

	/*res_origin.x = res_origin.x * scale;
	res_origin.y = res_origin.y * scale;
	res_origin.z = res_origin.z * scale;
	res_endpt.x = res_endpt.x * scale;
	res_endpt.y = res_endpt.y * scale;
	res_endpt.z = res_endpt.z * scale;*/
	MathWiz::translateToWindowSpace(res_origin);
	MathWiz::translateToWindowSpace(res_endpt);

	OctantWiz::Point3D color1 = obtainColor(res_origin.z);
	OctantWiz::Point3D color2 = obtainColor(res_endpt.z);

	unsigned int res_color1 = getColor(color1);
	unsigned int res_color2 = getColor(color2);

	LineRenderer::LiDDArender3D(draw, res_origin, res_endpt, zBuffer, res_color1, res_color2);
}

OctantWiz::Point3D Interpreter::obtainColor(double zvalue) {
	if (round(zvalue) == 0) {
		return near;
	}
	else if (round(zvalue) == zBufferMaxDistance) {
		return far;
	}
	else {
		double totalreddistance = (far.x - near.x);
		double totalgredistance = (far.y - near.y);
		double totalbludistance = (far.z - near.z);

		double red = zvalue / (zBufferMaxDistance - zBufferMin) * totalreddistance;
		double green = zvalue / (zBufferMaxDistance - zBufferMin) * totalgredistance;
		double blue = zvalue / (zBufferMaxDistance - zBufferMin) * totalbludistance;

		return OctantWiz::Point3D(red, green, blue);
	}
}

unsigned int Interpreter::getColor(OctantWiz::Point3D point) {
	point.x = point.x * 255;
	point.y = point.y * 255;
	point.z = point.z * 255;

	Color color(point);

	return color.getHex();
}

void Interpreter::SetCamera(double xlow, double ylow, double xhigh, double yhigh, double hither, double yon) {
	// Obtain Camera Matrix (Camera Space) by inversing CTM
	Matrix* inverseMatrix = MathWiz::InverseCTM(CTM);
	CameraSpace.SetSpace(inverseMatrix);

	//View Frustum handling
	ViewFrustum orig(xlow, ylow, xhigh, yhigh, hither, yon);
	CameraSpace.SetOriginal(orig);
	double xscale = 650 / (xhigh - xlow);
	double yscale = -1 * 650 / (yhigh - ylow);
	xlow = xlow * xscale + 325;
	ylow = ylow * yscale + 325;
	xhigh = xhigh * xscale + 325;
	yhigh = yhigh * yscale + 325;
	ViewFrustum view(xlow, ylow, xhigh, yhigh, hither, yon);
	CameraSpace.SetFrustum(view);
}
