#include "Matrix.h"
#include <iostream> 
#include <math.h>
#include <random>
#include <ctime>

Matrix::Matrix(int nr, int nc, float _mult){
	capacity = nr * nc * _mult;
	nrows = nr;
	ncols = nc;
	data = new double [capacity];
}

Matrix::Matrix(const Matrix & obj){
	nrows = obj.nrows;
	ncols = obj.ncols;
	data = new double [obj.nrows * obj.ncols];
	for (int i = 0; i < obj.nrows; i++){
		for (int j = 0; j < obj.ncols; j++){
			//(i, j) = obj(i, j);
			data[i * nrows + j] = obj(i, j);
			//this -> set(i, j, obj(i, j)); 
		}
	}
}

Matrix::~Matrix(){
	delete []data;
}

double & Matrix::operator()(int i, int j){
	return data[i * nrows + j];
}

const double & Matrix::operator()(int i, int j) const{
	return data[i * nrows + j];
}

Matrix & Matrix::operator = (const Matrix & obj){
	//(obj).show();
	delete[] data;
	nrows = obj.nrows;
	ncols = obj.ncols;
	data = new double [obj.nrows * obj.ncols];
	for (int i = 0; i < nrows; i++){
		for (int j = 0; j < ncols; j++){
			//(i, j) = obj(i, j);
			data[i * nrows + j] = obj(i, j);
		}
	}
	return *this;
}

void Matrix::show() const{
	for (int i = 0; i < nrows; i++){
		for (int j = 0; j < ncols; j++){
			std::cout << (*this)(i, j) << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

 Matrix operator + (const Matrix & A, const Matrix & B){
	Matrix C(A.nrows, A.ncols);
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			C.data[i * A.nrows + j] = A(i, j) + B(i, j);
		}
	}
	//C.show();
	return C;
}

Matrix & Matrix::operator += (const Matrix & A){
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			(*this).data[i * A.nrows + j] = (*this)(i, j) + A(i, j);
		}
	}
	return *this;
}

Matrix operator - (const Matrix & A, const Matrix & B){
	Matrix C(A.nrows, A.ncols);
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			C.data[i * A.nrows + j] = A(i, j) + B(i, j);
		}
	}
	return C;
}

Matrix & Matrix::operator -=(const Matrix & A){
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			(*this).data[i * A.nrows + j] = (*this)(i, j) - A(i, j);
		}
	}
	return *this;
}

Matrix operator *(const Matrix & A, const Matrix & B){
	Matrix C(A.nrows, A.ncols);
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			C.data[i * A.nrows + j] = 0;
		}
	}
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			for (int k = 0; k < A.nrows; k++){
				C.data[i * A.nrows + j] += A(i, k) * B(k, j);
			}
		}
	}
	return C;
}

Matrix & Matrix::operator *=(const Matrix & A){
	Matrix B = (*this);
	//Matrix C(A.nrows, A.ncols);
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			(*this).data[i * A.nrows + j] = 0;
		}
	}
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			for (int k = 0; k < A.nrows; k++){
				//(*this).data[i * A.nrows + j] = A(i, k) * B(k, j);
				(*this).data[i * A.nrows + j] += B(i, k) * A(k, j);
			}
		}
	}
	return *this;
}

Matrix operator *(const Matrix & A, double alpha){
	Matrix C(A.nrows, A.ncols);
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			C(i, j) = A(i, j) * alpha;
		}
	}
	return C;
}

Matrix operator *(double alpha, const Matrix & A){
	Matrix C(A.nrows, A.ncols);
	for (int i = 0; i < A.nrows; i++){
		for (int j = 0; j < A.ncols; j++){
			C(i, j) = A(i, j) * alpha;
		}
	}
	return C;
}

Matrix & Matrix::operator *=(double alpha){
	for (int i = 0; i < this -> nrows; i++){
		for (int j = 0; j < this -> ncols; j++){
			(*this)(i, j) *= alpha;
		}
	}
	return *this;
}

void swap (double& a, double& b){
	double c;
	c = a;
	a = b;
	b = c;
}

Matrix operator ~(const Matrix & A){
	Matrix res(A);
	for (int i = 0; i < A.ncols; i++){
		for (int j = 0; j < i; j++){
			swap(res(i, j), res(j, i));
		}
	}
	return res;
}

double Matrix::trace(){
	double rez = 0;
	for (int i = 0; i < this -> ncols; i++)
		rez += (*this)(i, i);
	return rez;
}

void Matrix::fillI(){
	for (int i = 0; i < this -> nrows; i++){
		for (int j = 0; j < this -> ncols; j++){
			if (i == j) (*this)(i, j) = 1;
			else (*this)(i, j) = 0;
		}
	}
}

void Matrix::fillRand(double beg, double end){
	srand(int(time(NULL)));
	for (int i = 0; i < this -> nrows; i++){
		for (int j = 0; j < this -> ncols; j++){
			(*this)(i, j) = (rand()%long(1000 * (end-beg))) / 1000. + beg;
		}
	}
}

void Matrix::set(int row, int col, double val){
	data[(row - 1) * nrows + col - 1] = val;
}

void Matrix::set(double* arr){
	int counter = 0;
	for (int i = 0; i < nrows; i++){
		for (int j = 0; j < ncols; j++){
			(*this)(i, j) = arr[counter];
			counter++;
		}
	}
}

void Matrix::power(int expon){
	Matrix a = (*this);
	for (int i = 1; i < expon; i++){
		(*this) *= a;
	}
}

double Matrix::det(){			// (строка, столбец)
	double mult = 1;
	double tmp = 1;
	double res = 1;
	int tmpRow = 0;
	Matrix tmpMx(nrows, ncols);
	tmpMx = (*this);
	for (int i = 0; i < nrows; i ++){ // столбцы
		for (int j = tmpRow; j < ncols; j++){ // строки
			if (tmpMx(j, i) != 0){
				/*mult *= (*this)(j, i);*/
				mult *= tmpMx(j, i);
				tmp = tmpMx(j, i);
				for (int k = i; k < nrows; k++){ // столбцы
					tmpMx(j, k) = tmpMx(j, k) * 1. / tmp;
				}
			}
		}
		//(*this).show();
		for (int t = tmpRow + 1; t < ncols; t++){ //строки
			if (tmpMx(t, t - 1) != 0)
				for (int u = i; u < nrows; u++){ //столбцы
					tmpMx(t, u) -= tmpMx(i, u);
			}
		}
		//(*this).show();
		tmpRow++;
	}
	for (int i = 0; i < ncols; i++)
		res *= tmpMx(i, i);
	return (res * 1. * mult);
}

Matrix Matrix::invert(){
	double baseDet = (*this).det();
	Matrix C(nrows, ncols);
	Matrix temp(nrows - 1, ncols - 1);
	for (int k = 0; k < nrows; k++){ //строка 
		for (int t = 0; t < nrows; t++){ //столбец
			for (int i = 0; i < nrows; i++){ //строка для минора
				for (int j = 0; j < nrows; j++){ //столбец для минора
					if (i < k && j < t)
						temp(i, j) = (*this)(i, j);
					else if (i < k && j > t)
						temp(i, j - 1) = (*this)(i, j);
					else if (i > k && j < t)
						temp(i - 1, j) = (*this)(i, j);
					else if (i > k && j > t)
						temp(i - 1, j - 1) = (*this)(i, j);
					//temp.show();
				}
			}
			//temp.show();
			if ((t + k) % 2 == 0) 
				C(t, k) = temp.det() / baseDet;
			else C(t, k) = -1 * temp.det() / baseDet;
		}
	}
	return C;
}