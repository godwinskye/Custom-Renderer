#pragma once
#include <string>
#include <fstream>
#include "renderarea361.h"

#define ALTER

class ObjParser {
public:
	ObjParser(Drawable *drawable, std::string filename);

	void interpretStream(std::ifstream& stream);
	void interpretLine(std::string line);

	std::string appendSubsequentAlphabets(std::string line, int &position);
	void fitToken(std::string token, std::string line, int &position);

	std::ifstream file;
private:
	Drawable* draw;
};