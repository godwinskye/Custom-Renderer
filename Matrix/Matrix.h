#pragma once

enum class MType {
	BACK_PLANE,
	IDENTITY,
	ZERO
};

enum class Axis {
	XAXIS,
	YAXIS,
	ZAXIS
};

class Matrix {
public:
	Matrix(int row, int column, MType);
	Matrix(Matrix* original);					//deep copy
	~Matrix();

	double at(int x, int y);

	void setAt(int x, int y, double newvalue);
	void setAll(double newvalue);
	void setIdentity();

	int index(int x, int y) const;

	int getRow();
	int getWidth();
private:
	double* marray;
	int width;
	int size;
	int row;
	static const int BACK_CLIPPING_PLANE = 200;
};