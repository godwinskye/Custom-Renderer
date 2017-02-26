#pragma once

class Matrix {
public:
	Matrix(int row, int column);
	~Matrix();
	int at(int x, int y);
	void setAt(int x, int y, int newvalue);
	int index(int x, int y) const;
private:
	int* marray;
	int width;
};