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
		if (line[i] == ' ' || line[i] == '\n') {
			continue;
		}
		else if (line[i] == '{') {
			CTMstack.push(CTM);
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
		if (isdigit(line[position])) {
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
}

//position at WHITESPACE or NEWLINE
void Interpreter::fitToken(std::string token, std::string line, int &position) {
	if (token == "polygon") {
		OctantWiz::Point3D origin(grabNextNum(line, position), grabNextNum(line, position), grabNextNum(line, position));
		OctantWiz::Point3D endpoint1(grabNextNum(line, position), grabNextNum(line, position), grabNextNum(line, position));
		OctantWiz::Point3D endpoint2(grabNextNum(line, position), grabNextNum(line, position), grabNextNum(line, position));
		RenderPolygon(origin, endpoint1, endpoint2);
	}
	else if (token == "line") {
		OctantWiz::Point3D origin(grabNextNum(line, position), grabNextNum(line, position), grabNextNum(line, position));
		OctantWiz::Point3D endpoint(grabNextNum(line, position), grabNextNum(line, position), grabNextNum(line, position));
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
		//TODO: Write file-reader
	}
	else if (token == "wire") {
		FILLED = false;
	}
	else if (token == "filled") {
		FILLED = true;
	}
}

void Interpreter::ScaleCTM(double sx, double sy, double sz) {
	Matrix scaler = MathWiz::makeScaleFactorMatrix(sx, sy, sz);
	CTM = MathWiz::matrixMultiplication(CTM, scaler);
	delete[] & scaler;
}

void Interpreter::TranslateCTM(double tx, double ty, double tz) {
	Matrix translation = MathWiz::makeTranslationMatrix(tx, ty, tz);
	CTM = MathWiz::matrixMultiplication(CTM, translation);
	delete[] & translation;
}

void Interpreter::RotateCTM(Axis axis, double degrees) {
	switch (axis) {
		case Axis::XAXIS: {
			Matrix rotation = MathWiz::makeXRotation(degrees);
			CTM = MathWiz::matrixMultiplication(CTM, rotation);
			delete[] & rotation;
			break;
		}
		case Axis::YAXIS: {
			Matrix rotation = MathWiz::makeYRotation(degrees);
			CTM = MathWiz::matrixMultiplication(CTM, rotation);
			delete[] & rotation;
			break;
		}
		case Axis::ZAXIS: {
			Matrix rotation = MathWiz::makeZRotation(degrees);
			CTM = MathWiz::matrixMultiplication(CTM, rotation);
			delete[] & rotation;
			break;
		}
	}
}

void Interpreter::RenderPolygon(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint1, OctantWiz::Point3D endpoint2) {
	Matrix origin1 = MathWiz::PointToMatrix(origin);
	Matrix endpoint11 = MathWiz::PointToMatrix(endpoint1);
	Matrix endpoint22 = MathWiz::PointToMatrix(endpoint2);

	Matrix torigin = MathWiz::matrixMultiplication(CTM, origin1);
	Matrix tendpoint1 = MathWiz::matrixMultiplication(CTM, endpoint11);
	Matrix tendpoint2 = MathWiz::matrixMultiplication(CTM, endpoint22);

	OctantWiz::Point3D res_origin = MathWiz::MatrixToPoint(torigin);
	OctantWiz::Point3D res_endpt1 = MathWiz::MatrixToPoint(tendpoint1);
	OctantWiz::Point3D res_endpt2 = MathWiz::MatrixToPoint(tendpoint2);

	res_origin.x = res_origin.x * scale;
	res_origin.y = res_origin.y * scale;
	res_origin.z = res_origin.z * scale;
	res_endpt1.x = res_endpt1.x * scale;
	res_endpt1.y = res_endpt1.y * scale;
	res_endpt1.z = res_endpt1.z * scale;
	res_endpt2.x = res_endpt2.x * scale;
	res_endpt2.y = res_endpt2.y * scale;
	res_endpt2.z = res_endpt2.z * scale;

	delete[] & origin1;
	delete[] & endpoint11;
	delete[] & endpoint22;

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

void Interpreter::RenderLine(OctantWiz::Point3D origin, OctantWiz::Point3D endpoint) {
	Matrix origin1 = MathWiz::PointToMatrix(origin);
	Matrix endpoint11 = MathWiz::PointToMatrix(endpoint);

	Matrix torigin = MathWiz::matrixMultiplication(CTM, origin1);
	Matrix tendpoint1 = MathWiz::matrixMultiplication(CTM, endpoint11);

	OctantWiz::Point3D res_origin = MathWiz::MatrixToPoint(torigin);
	OctantWiz::Point3D res_endpt = MathWiz::MatrixToPoint(tendpoint1);

	res_origin.x = res_origin.x * scale;
	res_origin.y = res_origin.y * scale;
	res_origin.z = res_origin.z * scale;
	res_endpt.x = res_endpt.x * scale;
	res_endpt.y = res_endpt.y * scale;
	res_endpt.z = res_endpt.z * scale;

	delete[] & origin1;
	delete[] & endpoint11;

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
		double totalreddistance = abs(far.x - near.x);
		double totalgredistance = abs(far.y - near.y);
		double totalbludistance = abs(far.z - near.z);

		double red = zvalue / zBufferMaxDistance * totalreddistance;
		double green = zvalue / zBufferMaxDistance * totalgredistance;
		double blue = zvalue / zBufferMaxDistance * totalbludistance;

		return OctantWiz::Point3D(red, green, blue);
	}
}

unsigned int Interpreter::getColor(OctantWiz::Point3D point) {
	unsigned int red = point.x * 255;
	unsigned int green = point.y * 255;
	unsigned int blue = point.z * 255;

	unsigned int colour = (0xff << 24) + ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
	return colour;
}
