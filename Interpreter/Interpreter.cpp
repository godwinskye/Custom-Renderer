#include "Interpreter.h"
#include <iostream>

#define ALTER

Interpreter::Interpreter(std::string filename) {
	filename += ".simp";
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
			//TODO: OPEN_BRACE
		}
		else if (line[i] == '}') {
			//TODO: CLOSE_BRACE
		}
		else {
			token = appendSubsequentAlphabets(line, ALTER i);
			fitToken(line, ALTER i);
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
//TODO: Fill fitToken
//position at WHITESPACE or NEWLINE
void Interpreter::fitToken(std::string token, int &position) {
	if (token == "polygon") {
		//code
	}
	else if (token == "line") {
		//code
	}
	else if (token == "scale") {
		//code
	}
	else if (token == "rotate") {
		//code
	}
	else if (token == "translate") {
		//code
	}
	else if (token == "file") {
		//code
	}
	else if (token == "wire") {
		//code
	}
	else if (token == "filled") {
		//code
	}
}
