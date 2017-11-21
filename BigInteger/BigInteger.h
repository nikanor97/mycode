#pragma once;
const int size = 350; // � ����� ����������� ������ ���� �������
const int expon = 10; // ����, ���� ������� �����

class BigInt{
	int *data;
	bool sign;
public:
	BigInt();
	template <typename T> BigInt(T);
	BigInt(char*);
	BigInt(const BigInt& obj);
	~BigInt();
	friend BigInt operator +(const BigInt&, const BigInt&);
	friend BigInt operator -(const BigInt&, const BigInt&);
	friend BigInt operator *(const BigInt&, const BigInt&);
	friend BigInt operator /(const BigInt&, const BigInt&);
	int countsign();
	const int countsign() const;
	void clear();
	BigInt sqrt();
	friend BigInt GCD(const BigInt&, const BigInt&); // the greatest common divisor
	BigInt& multexpon(int a); // �� ������� ���� �������� ����� ������� (������� ���� ���������, ����� ������� �������� ������ ���������� ����� ���������), ��� ��� �� ���� ��� �� �����
	BigInt friend leftover(const BigInt& a, const BigInt& b);
	BigInt& operator =(const BigInt&);
	int& operator [](int);
	const int & operator [] (int) const;
	void set(char*);
	void set(BigInt a, int beg, int end);
	void get();
	const void get() const;
	int friend compare(const BigInt&, const BigInt&);
};