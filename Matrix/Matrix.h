#pragma once
class Matrix {
  double * data;    // массив для хранения чисел
  int capacity;     // размер этого массива
  float multiplier; // число >= 1 и равное capacity / (nrows * ncols)
public:
  int nrows, ncols;

  Matrix (int nr = 1, int nc = 1, float _multiplier = 1.5f);
  Matrix(const Matrix & obj);  
  ~Matrix();  
  Matrix & operator = (const Matrix & obj);
  //Операторы индексации
  double & operator()(int i, int j);
  const double & operator()(int i, int j) const;
  void show () const;
  //Сложение матриц
  friend Matrix operator +(const Matrix & A, const Matrix & B);
			Matrix & operator +=(const Matrix & A);
  //Вычитание матриц
  friend Matrix operator -(const Matrix & A, const Matrix & B);
			Matrix & operator -=(const Matrix & A);
  //Умножение матриц
  friend Matrix operator *(const Matrix & A, const Matrix & B);
			Matrix & operator *=(const Matrix & A);
  //Умножение матрицы на число
  friend Matrix operator *(const Matrix & A, double alpha);
  friend Matrix operator *(double alpha, const Matrix & A);
			Matrix & operator *=(double alpha);
  //Обращение матрицы
  friend Matrix invert(const Matrix & A);  
  Matrix  invert();
  //Транспонирование матрицы
  friend Matrix operator ~(const Matrix & A);
  Matrix & operator ~();
  //Вычисление детерминанта
  double det();
			//Вычисление следа матрицы
			double trace();
			//Заполнение матрицы случайными числами в заданном диапазоне
			void fillRand(double beg = 0.0, double end = 1.0);
			//Заполнить единичной матрицей
			void fillI();

  void power(int expon);
  void set(int row, int col, double val);
  void set(double* arr);
};