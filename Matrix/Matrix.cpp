#include "Matrix.h"
#include <math.h>

Matrix::Matrix(int row, int column, MType type) {
	size = row * column;
	marray = new double[size];
	width = column;
	this->row = row;
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

//deep copy
Matrix::Matrix(Matrix * original) {
	size = original->getRow() * original->getWidth();
	marray = new double[size];
	width = original->getWidth();
	this->row = original->getRow();
	for (int i = 0; i < size; i++) {
		marray[i] = original->marray[i];
	}
}

Matrix::~Matrix() {
	delete[] marray;
}

double Matrix::at(int x, int y) {
	return marray[index(x, y)];
}

void Matrix::setAt(int x, int y, double newvalue) {
	marray[x * width + y] = newvalue;
}

void Matrix::setAll(double newvalue) {
	for (int i = 0; i < size; i++) {
		marray[i] = newvalue;
	}
}

void Matrix::setIdentity() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < width; j++) {
			if (i == j) {
				setAt(i, j, 1);
			}
			else {
				setAt(i, j, 0);
			}
		}
	}
}

int Matrix::index(int x, int y) const {
	return x * width + y;              //x + width * y
}

int Matrix::getRow() {
	return row;
}

int Matrix::getWidth() {
	return width;
}
