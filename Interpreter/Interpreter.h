#pragma once
#include <string>
#include <fstream>

class Interpreter {
public:
	Interpreter(std::string filename);

	void interpretStream(std::ifstream &stream);
	void interpretLine(std::string line);
	std::string appendSubsequentAlphabets(std::string line, int &position);
	void applyToken(std::string token, int &position);

	std::ifstream mainfile;
	std::ifstream subfile;			//prototype
private:
	//code
};