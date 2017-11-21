//#pragma once
#include "BigInteger.h"
#include <iostream>
#include <cstring>
#include <math.h>
#include <cstdio>

using namespace std; //bad moment, but makes code shorter

template <> BigInt::BigInt(char);
template <> BigInt::BigInt(double);

BigInt::BigInt(){
	sign = true;
	data = new int[size];
	for (int i = 0; i < size; i++){
		data[i] = 0;
	}
}

template <typename T> BigInt::BigInt(T a){
	if (a >= 0) sign = true;
	else sign = false;
	a = abs(a);
	data = new int[size];
	for (int i = 0; i < size; i++){
		data[i] = 0;
	}
	int k = 0;
	int b = 0;
	int temp;
	do{
		(*this)[k] = ((a % int(pow(expon * 1., (k + 1) * 1.))) - b) / pow(expon * 1., k * 1.);
		temp = (*this)[k];
		b += (*this)[k] * pow(expon * 1., k * 1.);
		k++;
	}
	while (a >= pow(expon * 1., k * 1.));
}

BigInt::BigInt(char* str){
	int len = strlen(str); 
	for (int i = 0; i < len; i++){
		if (str[i] == '-'){
			(*this).sign = false;
			break;
		}
	}
	//cout << this -> sign << endl; //
	/*if (a >= 0) sign = true;
	else sign = false;*/
	data = new int[size];
	for (int i = 0; i < size; i++){
		data[i] = 0;
	}
	//int len = strlen(str); 
	int i = 0;
	int temp;
	char c;
	//BigInt res;
	//this -> get();
	for (int i = 0; i < len; i++){
		c = str[i];
		if (c == '-') c = '0';
		temp = c - '0';
		//BigInt x(10);
		//x.get();
		(*this) = (*this) * 10;
		//cout << endl; //
		//(*this).get();//
		//cout << endl; //
		//cout << this -> sign << endl; //
		(*this) = (*this) + temp;
		//(*this).get();//
		//ns;
		//cout << endl; //
	}
	//(*this) = res;
}

BigInt::~BigInt(){
	delete [] data;
}

void BigInt::clear(){
	for (int i = 0; i < size; i++){
		(*this)[i] = 0;
	}
}

int& BigInt::operator [](int i){
	return data[(size - 1) - i];
}

const int &BigInt::operator [] (int i) const{
	return data[(size - 1) - i];
}

BigInt::BigInt(const BigInt& obj){
	sign = obj.sign;
	data = new int[size];
	for (int i = 0; i < size; i++){
		data[i] = 0;
	}
	for (int i = 0; i < size; i++){
		//int temp1 = (*this)[i];
		//int temp2 = obj[i];
		(*this)[i] = obj[i];
		//(*this).data[i] = obj.data[i];
	}
}

BigInt& BigInt::operator=(const BigInt& a){
	sign = a.sign;
	for (int i = 0; i < size; i++){
		(*this)[i] = a[i];
	}
	return *this;
}

BigInt operator +(const BigInt& a, const BigInt& b){
	//a.get(); //
	//cout << endl; //
	//b.get(); //
	//cout << endl; //
	BigInt c;
	//cout << a.sign << b.sign; //
	if (a.sign == true && b.sign == true || a.sign == false && b.sign == false){
		for (int i = 0; i < size; i++){
			c[i] = a[i] + b[i];
			//cout << c[i] << endl; //
		}
		//c.get(); //
		//cout << endl; //
		for (int i = 0; i < size; i++){
			if (c[i] >= expon){ 
				c[i + 1] = c[i + 1] + 1;
				c[i] = c[i] - expon;
			}
			//cout << c[i] << endl; //
		}
		if (a.sign == false && b.sign == false) c.sign = false;
	}
	if (a.sign == true && b.sign == false) c = a - b;
	if (a.sign == false && b.sign == true) c = b - a;
	return c;
}

BigInt operator -(const BigInt& a, const BigInt& b){
	BigInt c;
	//для отрицательного результата
	if (compare(a, b) == 2 && a.sign == true && b.sign == true){
		c = b - a;
		c.sign = false;
		return c;
	}
	//
	if (a.sign == true && b.sign == true || a.sign == false && b.sign == false){
		for (int i = 0; i < size; i++){
			c[i] = a[i] - b[i];
		}
		for (int i = 0; i < size; i++){
			if (c[i] < 0){ 
				c[i + 1] = c[i + 1] - 1;
				c[i] = c[i] + expon;
			}
		}
		if (a.sign == false && b.sign == false)
			c.sign = false;
	}
	if (a.sign == true && b.sign == false){
		c = a + b;
		c.sign = true;
	}
	if (a.sign == false && b.sign == true){
		c = a + b;
		c.sign = false;
	}
	return c;
}

BigInt operator *(const BigInt& a, const BigInt& b){
	BigInt c;
	//a.get();
	//b.get();
	for (int i = 0; i < size; i++){
		for (int j = 0; j <= i; j++){
			//if (c[i] == -1) c[i] = 0;
			int t1 = c[i]; //
			int t2 = a[j]; //
			int t3 = b[i - j]; //
			if (b[i - j] == 0 || a[j] == 0) continue;
			//c[i] = c[i] + a[j] + b[i - j];
			c[i] = c[i] + a[j] * b[i - j];
		}
	}
	//c.get(); //
	for (int i = 0; i < size; i++){
		if (c[i] >= expon){ 
			int t1 = c[i];
			int t2 = c[i + 1];
			//c[i + 1] = c[i + 1] + (c[i] % expon);
			c[i + 1] = c[i + 1] + ((c[i] - c[i] % expon) / expon);
			//c[i] = c[i] - expon * (c[i] % expon);
			c[i] = c[i] - expon * ((c[i] - c[i] % expon) / expon);
		}
	}
	//c.get(); //
	if (a.sign == true && b.sign == true || a.sign == false && b.sign == false)
		c.sign == true;
	if (a.sign == true && b.sign == false || a.sign == false && b.sign == true)
		c.sign == false;
	//cout << c.sign << endl; // ЗНАК ПЛОХО УЧИТЫВАЕТСЯ
	return c;
}

int BigInt::countsign(){
	for (int i = size - 1; i >= 0; i--){
		if ((*this)[i] != 0)
			return (i + 1);
	}
	return 0;
}

const int BigInt::countsign() const{
	for (int i = size - 1; i >= 0; i--){
		if ((*this)[i] != 0)
			return (i + 1);
	}
	return 0;
}

BigInt operator /(const BigInt& a, const BigInt& b){
	BigInt leftover;	// остаток
	BigInt result;		// результат деления
	BigInt temp;		// вспомогательная переменная в которой храню делимое подчисло
	BigInt templeft;	// остоток от локального деления
	int alen = a.countsign(); // запоминаем длину делимого
	int blen = b.countsign(); // запоминаем длину делителя
	int i = 0;	// счетчик
	for (;;){
		temp.clear();
		temp = templeft;
		templeft.clear();
		//temp.get(); //
		//cout << endl; //
		if (alen - blen - i < 0){		// проверка на то, не пора ли остановиться
			leftover = a - result * b;	// запоминаем остаток
			break;
		}
		if (i != 0){
			temp = temp * expon + a[alen - blen - i];
			//temp.get(); //
			//cout << endl; //
			//*******	на случай деления типа 123 / 12
			if (compare(temp, b) == 2 && alen - blen - i == 0){
				result = result * expon;
				leftover = a - result * b;
				break;
			}
			//*******
			if (compare(temp, b) == 2 && compare(temp, 0) != 0){
				i++;
				//***************
				if (alen - blen - i < 0){		
					leftover = a - result * b;	
					break;
				}
				//***************
				temp = temp * expon + a[alen - blen - i];
				result = result * expon;
			}
		}
		if (i == 0){
			temp.set(a, alen - blen, alen - 1);	// кусок делимого, который буду делить
			//temp.get(); //
			//cout << endl; //
			if (compare(temp, b) == 2){			// проверка на то, не выделить ли еще цифру
				//temp.clear();
				//temp.set(a, alen - blen - 1, alen - 1);
				i++;
				//***************
				if (alen - blen - i < 0){		
					leftover = a - result * b;	
					break;
				}
				//***************
				temp = temp * expon + a[alen - blen - 1];
			}
		}
		//cout << endl; //
		//temp.get(); //
		//cout << endl; //
		for (int j = 1; j <= 10; j++){			// подбор цифры, которая пойдет в частное
			if (compare(temp, b * j) == 0){
				result = result * expon + j;
				templeft = temp - j * b;
				break;
			}
			if (compare(temp, b * j) == 2){
				result = result * expon + (j - 1);
				templeft = temp - (j - 1) * b;
				break;
			}
		}
		//result.get(); //
		//cout << endl; //
		i++;
	}
	//leftover.get(); //
	//cout << endl; //
	return result;
}

BigInt leftover(const BigInt& a, const BigInt& b){
	BigInt leftover;	// остаток
	BigInt result;		// результат деления
	BigInt temp;		// вспомогательная переменная в которой храню делимое подчисло
	BigInt templeft;	// остоток от локального деления
	int alen = a.countsign(); // запоминаем длину делимого
	int blen = b.countsign(); // запоминаем длину делителя
	int i = 0;	// счетчик
	for (;;){
		temp.clear();
		temp = templeft;
		templeft.clear();
		//temp.get(); //
		//cout << endl; //
		if (alen - blen - i < 0){		// проверка на то, не пора ли остановиться
			leftover = a - result * b;	// запоминаем остаток
			break;
		}
		if (i != 0){
			temp = temp * expon + a[alen - blen - i];
			//temp.get(); //
			//cout << endl; //
			//*******	на случай деления типа 123 / 12
			if (compare(temp, b) == 2 && alen - blen - i == 0){
				result = result * expon;
				leftover = a - result * b;
				break;
			}
			//*******
			if (compare(temp, b) == 2 && compare(temp, 0) != 0){
				i++;
				//***************
				if (alen - blen - i < 0){		
					leftover = a - result * b;	
					break;
				}
				//***************
				temp = temp * expon + a[alen - blen - i];
				result = result * expon;
			}
		}
		if (i == 0){
			temp.set(a, alen - blen, alen - 1);	// кусок делимого, который буду делить
			//temp.get(); //
			//cout << endl; //
			if (compare(temp, b) == 2){			// проверка на то, не выделить ли еще цифру
				//temp.clear();
				//temp.set(a, alen - blen - 1, alen - 1);
				i++;
				//***************
				if (alen - blen - i < 0){		
					leftover = a - result * b;	
					break;
				}
				//***************
				temp = temp * expon + a[alen - blen - 1];
			}
		}
		//cout << endl; //
		//temp.get(); //
		//cout << endl; //
		for (int j = 1; j <= 10; j++){			// подбор цифры, которая пойдет в частное
			if (compare(temp, b * j) == 0){
				result = result * expon + j;
				templeft = temp - j * b;
				break;
			}
			if (compare(temp, b * j) == 2){
				result = result * expon + (j - 1);
				templeft = temp - (j - 1) * b;
				break;
			}
		}
		//result.get(); //
		//cout << endl; //
		i++;
	}
	//leftover.get(); //
	//cout << endl; //
	return leftover;
}

void BigInt::set(char* str){
	for (int i = 0; i < size; i++)
		if (str[i] == '-'){ 
			(*this).sign = false;
			break;
		}
	for (int i = 0; i < size; i++)
		(*this)[i] = 0;
	int len = strlen(str); // yt thbrvbrtiovbrtib
	int i = 0;
	int temp;
	char c;
	//BigInt res;
	//this -> get();
	for (int i = 0; i < len; i++){
		c = str[i];
		if (c == '-') c = '0';
		temp = c - '0';
		//BigInt x(10);
		//x.get();
		(*this) = (*this) * 10;
		//cout << endl; //
		//(*this).get();//
		//cout << endl; //
		(*this) = (*this) + temp;
		//(*this).get();//
		//cout << endl; //
	}
	//(*this) = res;
}

void BigInt::set(BigInt a, int beg, int end){//beg  и end - номера разрядов
	for (int i = end; i  >= beg; i--){	// счет разрядов идет с нулевого
		(*this) = (*this) * expon + a[i];
	}
}

void BigInt::get(){
	bool flag1 = false;
	bool flag2 = false;
	bool ifOnlyZero = true;
	int i = size - 1;
	if (this -> sign == false) cout << '-';
	do{
		if ((*this)[i] == 0) flag1 = true;
		if ((*this)[i] != 0) ifOnlyZero = false;
		if (flag1 == true && (*this)[i] != 0) flag2 = true;
		if ((*this)[i] != -1 &&( flag1 == true && flag2 == true || flag1 == false && flag2 == false)) cout << (*this)[i];
		i--;
		//flag1 = flag2 = false;
	}
	while (i >= 0);
	if (ifOnlyZero == true) cout << "0";
}

const void BigInt::get() const{
	bool flag1 = false;
	bool flag2 = false;
	bool ifOnlyZero = true;
	int i = size - 1;
	if (this -> sign == false) cout << '-';
	do{
		if ((*this)[i] == 0) flag1 = true;
		if ((*this)[i] != 0) ifOnlyZero = false;
		if (flag1 == true && (*this)[i] != 0) flag2 = true;
		if ((*this)[i] != -1 &&( flag1 == true && flag2 == true || flag1 == false && flag2 == false)) cout << (*this)[i] << " ";
		i--;
		//flag1 = flag2 = false;
	}
	while (i >= 0);
	if (ifOnlyZero == true) cout << "0";
}

int compare(const BigInt& a, const BigInt& b){
	for (int i = size - 1; i >=0; i--){
		if (a[i] > b[i] && a.sign == true && b.sign == true || 
			a.sign == true && b. sign == false ||
			a[i] < b[i] && a.sign == false && b.sign == false) return 1;
		if (a[i] < b[i] && a.sign == true && b.sign == true || 
			a.sign == false && b. sign == true ||
			a[i] > b[i] && a.sign == false && b.sign == false) return 2;
	}
	return 0;
}

BigInt& BigInt::multexpon(int a){
	for (int i = size - 1; i >= a; i--){
		(*this)[i] = (*this)[i - a];
		//cout << endl << "temp" << endl; //
		//this -> get(); //
	}
	for (int j = 0; j < a; j++)
		(*this)[j] = 0;
	return *this;
}

BigInt BigInt::sqrt(){
	int len = this -> countsign();
	BigInt result;
	int reslen;
	if (len % 2 == 0) reslen = len / 2;
	else reslen = len / 2 + 1;
	for (int i = 1; i <= reslen; i++){
		for (int j = 1; j <= 10; j++){
			result[reslen - i] = j;
			//cout << endl; //
			//result.get(); //
			if (compare(result * result, (*this)) == 0){
				goto finish;
			}
			if (compare(result * result, (*this)) == 1){
				result[reslen - i] = j - 1;
				break;
			}
		}
	}
finish:
	return result;
}

BigInt GCD(const BigInt& x, const BigInt& y){
	BigInt result;
	BigInt a(x);
	BigInt b(y);
	for (;;){
		if (compare(a, 0) == 0) return b;
		if (compare(b, 0) == 0) return a;
		if (compare(a, b) == 1){
			a = leftover(a, b);
			continue;
		}
		if (compare(a, b) == 2){
			b = leftover(b, a);
			continue;
		}
		if (compare(a, b) == 0){
			return a;	
		}
	}
}

//int main(){
//	char str1[300], str2[300];
//	cin >> str1;
//	cin >> str2;
//	//long t = 787665343545;
//	BigInt a(str1);
//	BigInt b(str2);
//	BigInt c;
//	c = a + b;
//	c.get();
//	system("pause");
//	return 0;
//}
