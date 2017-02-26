#include "Matrix.h"
#include <math.h>

Matrix::Matrix(int row, int column, MType type) {
	marray = new double[row * column];
	width = column;
	this->row = row;
	size = row * column;
	switch (type) {
	case MType::BACK_PLANE:
		setAll(BACK_CLIPPING_PLANE);
		break;
	case MType::IDENTITY:
		setIdentity();
		break;
	case MType::ZERO:
		setAll(0);
		break;
	}
}

Matrix::~Matrix() {
	delete[] marray;
}

double Matrix::at(int x, int y) {
	return marray[index(x, y)];
}

void Matrix::setAt(int x, int y, double newvalue) {
	marray[x + width * y] = newvalue;
}

void Matrix::setAll(double newvalue) {
	for (int i = 0; i < size; i++) {
		marray[i] = newvalue;
	}
}

void Matrix::setIdentity() {
	int side = sqrt(size);
	for (int i = 0; i < side; i++) {
		for (int j = 0; j < side; j++) {
			if (i == j) {
				marray[j] = 1;
			}
			else {
				marray[j] = 0;
			}
		}
	}
}

int Matrix::index(int x, int y) const {
	return x + width * y;
}

int Matrix::getRow() {
	return row;
}

int Matrix::getWidth() {
	return width;
}
