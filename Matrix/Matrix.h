#pragma once
class Matrix {
  double * data;    // ������ ��� �������� �����
  int capacity;     // ������ ����� �������
  float multiplier; // ����� >= 1 � ������ capacity / (nrows * ncols)
public:
  int nrows, ncols;

  Matrix (int nr = 1, int nc = 1, float _multiplier = 1.5f);
  Matrix(const Matrix & obj);  
  ~Matrix();  
  Matrix & operator = (const Matrix & obj);
  //��������� ����������
  double & operator()(int i, int j);
  const double & operator()(int i, int j) const;
  void show () const;
  //�������� ������
  friend Matrix operator +(const Matrix & A, const Matrix & B);
			Matrix & operator +=(const Matrix & A);
  //��������� ������
  friend Matrix operator -(const Matrix & A, const Matrix & B);
			Matrix & operator -=(const Matrix & A);
  //��������� ������
  friend Matrix operator *(const Matrix & A, const Matrix & B);
			Matrix & operator *=(const Matrix & A);
  //��������� ������� �� �����
  friend Matrix operator *(const Matrix & A, double alpha);
  friend Matrix operator *(double alpha, const Matrix & A);
			Matrix & operator *=(double alpha);
  //��������� �������
  friend Matrix invert(const Matrix & A);  
  Matrix  invert();
  //���������������� �������
  friend Matrix operator ~(const Matrix & A);
  Matrix & operator ~();
  //���������� ������������
  double det();
			//���������� ����� �������
			double trace();
			//���������� ������� ���������� ������� � �������� ���������
			void fillRand(double beg = 0.0, double end = 1.0);
			//��������� ��������� ��������
			void fillI();

  void power(int expon);
  void set(int row, int col, double val);
  void set(double* arr);
};