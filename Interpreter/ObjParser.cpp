#include "ObjParser.h"

ObjParser::ObjParser(Drawable * drawable, std::string filename) {
	filename += ".obj";
	draw = drawable;
	ALTER file.open(filename, std::ifstream::in);
	interpretStream(file);
}

void ObjParser::interpretStream(std::ifstream & stream) {
	std::string line;
	while (stream.good()) {
		std::getline(stream, line);
		interpretLine(line);
	}
}

void ObjParser::interpretLine(std::string line) {
	std::string token;
	//check if comment
	if (line[0] == '#') {
		return;
	}
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t') {
			continue;
		}
		token = appendSubsequentAlphabets(line, ALTER i);
		fitToken(token, line, ALTER i);
	}
}

std::string ObjParser::appendSubsequentAlphabets(std::string line, int & position) {
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

void ObjParser::fitToken(std::string token, std::string line, int & position) {
	if (token == "v") {
		//vertex
	}
	else if (token == "f") {
		//face
	}
	else if(token == "")
}
