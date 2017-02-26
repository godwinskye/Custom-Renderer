#include "Matrix.h"

Matrix::Matrix(int row, int column) {
	marray = new int[row * column];
	width = row;
	size = row * column;
	setAll(BACK_CLIPPING_PLANE);
}

Matrix::~Matrix() {
	delete[] marray;
}

int Matrix::at(int x, int y) {
	return marray[index(x, y)];
}

void Matrix::setAt(int x, int y, int newvalue) {
	marray[x + width * y] = newvalue;
}

void Matrix::setAll(int newvalue) {
	for (int i = 0; i < size; i++) {
		marray[i] = newvalue;
	}
}

int Matrix::index(int x, int y) const {
	return x + width * y;
}
