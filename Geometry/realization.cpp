#pragma once
#include <iostream>
#include <fstream>
#include <math.h>
#include "Geometry.h"

using namespace std;

Point::Point(){
	x = 0; 
	y = 0;
}

Point::Point(int a, int b){
	x = a; 
	y = b;
}

void Point::set(int a, int b){
	x = a;
	y = b;
}

Point::Point(const Point& obj){
	x = obj.x;
	y = obj.y;
}

Point& Point::operator = (const Point& a){
	x = a.x;
	y = a.y;
	return (*this);
}

bool Point::belongsToAngle(const Point& a, const Point& b, const Point& o){
	Vector v1(o, a);
	Vector v2(o, b);
	Vector vp(o, (*this));
	if (rotdir(v1, v2) == 1 && (rotdir(v1, vp) == 1 || rotdir(v1, vp) == 0) && 
		(rotdir(v2, vp) == 2 || rotdir(v2, vp) == 0) || 
		rotdir(v1, v2) == 2 && (rotdir(v1, vp) == 2 || rotdir(v1, vp) == 0) && 
		(rotdir(v2, vp) == 1 || rotdir(v2, vp) == 0))
		return true;
	else return false;
}

Point operator + (const Point& a, const Point& b){
	Point c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

Point operator - (const Point& a, const Point& b){
	Point c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

bool Point::IfOnSegment(const Point& a, const Point& b){ // проверка принадлежности точки отрезку, если известно, что точка лежит на прямой, содержащей отрезок
	if ((*this).x <= b.x && (*this).x >= a.x && (*this).y <= b.y && (*this).y >= a.y ||
		(*this).x >= b.x && (*this).x <= a.x && (*this).y <= b.y && (*this).y >= a.y ||
		(*this).x <= b.x && (*this).x >= a.x && (*this).y >= b.y && (*this).y <= a.y ||
		(*this).x >= b.x && (*this).x <= a.x && (*this).y >= b.y && (*this).y <= a.y){
			//cout << "true";
			return true;
	}
	else{ 
		//cout << "false";
		return false;
	}
}

const bool Point::IfOnSegment(const Point& a, const Point& b) const{ // проверка принадлежности точки отрезку, если известно, что точка лежит на прямой, содержащей отрезок
	if ((*this).x <= b.x && (*this).x >= a.x && (*this).y <= b.y && (*this).y >= a.y ||
		(*this).x >= b.x && (*this).x <= a.x && (*this).y <= b.y && (*this).y >= a.y ||
		(*this).x <= b.x && (*this).x >= a.x && (*this).y >= b.y && (*this).y <= a.y ||
		(*this).x >= b.x && (*this).x <= a.x && (*this).y >= b.y && (*this).y <= a.y){
			//cout << "true";
			return true;
	}
	else{ 
		//cout << "false";
		return false;
	}
}

Vector::Vector(int x1 = 0, int y1 = 0, int x0 = 0, int y0 = 0){
	beg.set(x0, y0);
	end.set(x1, y1);
}

Vector::Vector(const Point& p1, const Point& p2){
	beg = p1;
	end = p2;
}

Vector::Vector(const Vector& obj){
	beg = obj.beg;
	end = obj.end;
}

int rotdir(const Vector& v1, const Vector& v2){
	if ((v2.end.getx() - v2.beg.getx()) * (v1.end.gety() - v1.beg.gety()) - (v1.end.getx() - v1.beg.getx()) * 
		(v2.end.gety() - v2.beg.gety()) > 0)
		return 1; // по часовой
	else if ((v2.end.getx() - v2.beg.getx()) * (v1.end.gety() - v1.beg.gety()) - (v1.end.getx() - v1.beg.getx()) * 
		(v2.end.gety() - v2.beg.gety()) < 0)
		return 2; // против часовой
	else return 0; // совпадают
}

Segment::Segment(int x1 = 0, int y1 = 0, int x0 = 0, int y0 = 0){
	p1.set(x0, y0);
	p2.set(x1, y1);
}

Segment::Segment(const Point& a, const Point& b){
	p1 = a;
	p2 = b;
}

Segment::Segment(const Segment& obj){
	p1 = obj.p1;
	p2 = obj.p2;
}

bool intersect(const Segment& a, const Segment& b){
	Vector v1(a.p1, a.p2);
	Vector v2(a.p1, b.p1);
	Vector v3(a.p1, b.p2);
	Vector v4(a.p2, a.p1);
	Vector v5(a.p2, b.p1);
	Vector v6(a.p2, b.p2);
	Vector v7(b.p1, a.p1);
	Vector v8(b.p1, a.p2);
	Vector v9(b.p1, b.p2);
	Vector v10(b.p2, a.p1);
	Vector v11(b.p2, a.p2);
	Vector v12(b.p2, b.p1);
	if ((rotdir(v7, v9) != rotdir(v8, v9)) &&
		(rotdir(v5, v4) != rotdir(v6, v4)) &&
		(rotdir(v10, v12) != rotdir(v11, v12)) &&
		(rotdir(v2, v1) != rotdir(v3, v1)) ||
		//a.p1.IfOnSegment(b.p1, b.p2) || a.p2.IfOnSegment(b.p1, b.p2) ||
		//b.p1.IfOnSegment(a.p1, a.p2) || b.p2.IfOnSegment(a.p1, a.p2)
		//rotdir(v2, v1) == rotdir(v3, v1) && rotdir(v2, v1) == 0
		(rotdir(v2, v1) == rotdir(v3, v1) && rotdir(v2, v1) == 0 &&
		rotdir(v10, v12) == rotdir(v11, v12) && rotdir(v11, v12) == 0) &&
		(a.p1.IfOnSegment(b.p1, b.p2) || a.p2.IfOnSegment(b.p1, b.p2) ||
		b.p1.IfOnSegment(a.p1, a.p2) || b.p2.IfOnSegment(a.p1, a.p2))
		)
		return true;
	else return false;
	//else if (rotdir(v7, v9) == rotdir(v8, v9) && p2
}

double Segment::length(){
	return (sqrt(pow(abs((*this).p1.getx() - (*this).p2.getx()) * 1., 2) + 
		pow(abs((*this).p1.gety() - (*this).p2.gety()) * 1., 2)));
}

const double Segment::length() const{
	return (sqrt(pow(abs((*this).p1.getx() - (*this).p2.getx()) * 1., 2) + 
		pow(abs((*this).p1.gety() - (*this).p2.gety()) * 1., 2)));
}

int vectmult(const Vector& a, const Vector& b){
	int temp = (a.end.getx() - a.beg.getx()) * (b.end.gety() - b.beg.gety());
	int temp2 = (a.end.gety() - a.beg.gety()) * (b.end.getx() - b.beg.getx());
	return temp - temp2;
}

double distPointLine(const Point& a, const Segment& s){
	Vector v1(a, s.p1);
	Vector v2(a, s.p2);
	int mult = abs(vectmult(v1, v2));
	 return (mult / s.length());
}

double myabs(double x){
	if (x < 0) return -x;
	else return x;
}

double length(const Point& p1, const Point& p2){
	return sqrt(pow(abs(p1.getx() - p2.getx()) * 1., 2) + pow(abs(p2.gety() - p1.gety()) * 1., 2));
}

double length(double x1, double x2, double y1, double y2){
	return sqrt(pow(myabs(x1 - x2) * 1., 2) + pow(myabs(y2 - y1) * 1., 2));
}

double distPointSegment(const Point& a, const Segment& s){
	double h = distPointLine(a, s);
	double len = s.length();
	double side1 = length(a, s.p1);
	double side2 = length(a, s.p2);
	double temp = max(side1, side2);
	double controlTemp = sqrt(pow(temp, 2) - pow(h, 2));
	if (controlTemp < len) return h;
	else return min(side1, side2);
}

bool Point::belongsToSegment(const Segment& s){
	double dist1 = length((*this), s.p1);
	double dist2 = length((*this), s.p2);
	if (dist1 + dist2 == s.length()) return true;
	else return false;
}

Circle::Circle(){
	radius = 0;
	center = Point(0, 0);
}

Circle::Circle(const Point& p, int a){
	radius = a;
	center = p;
}

Circle::Circle(const Circle& obj){
	radius = obj.radius;
	center = obj.center;
}

double distPointLineDoubles(double x0, double y0, double A, double B, double C){
	return myabs((A * x0 + B * y0 + C) / sqrt(A * A + B * B));
}

bool intersectLineCircle(const Circle& c, double A, double B, double C){
	double x1, x2, y1, y2;
	int r = c.radius, xc = c.center.getx(), yc = c.center.gety();
	if (A == B && A == C && A == 0){
		return false;
	}
	double Cold = C;	//old version of C
	C = A * xc + B * yc + C;
	//double d = pow(A * xc + B * yc + C, 2) / (A * A + B * B);
	//cout << r * r * (A * A + B * B) - pow(C, 2);
	//cout << distPointLineDoubles(xc, yc, A, B, Cold);
	double t = sqrt(r * r * (A * A + B * B) - pow(C, 2)) * 1. / (A * A + B * B);
	double x0 = (-A * C) * 1. / (A * A + B * B), y0 = (-B * C) * 1. / (A * A + B * B);
	if (distPointLineDoubles(xc, yc, A, B, Cold) < r){
		x1 = x0 + B * t;
		x2 = x0 - B * t;
		y1 = y0 - A * t;
		y2 = y0 + A * t;
		printf("%s %s", "2", "\n");
		printf("%.5f %s %.5f %s", x1 + xc, " ", y1 + yc , "\n");
		printf("%.5f %s %.5f %s", x2 + xc, " ", y2 + yc , "\n");
	}
	if (distPointLineDoubles(xc, yc, A, B, Cold) == r){
		printf("%s %s", "1", "\n");
		printf("%.5f %s %.5f %s", x0 + xc, " ", y0 + yc, "\n");
	}
	if (distPointLineDoubles(xc, yc, A, B, Cold) > r){
		printf("%s", "0");
	}
	return true;
}

bool intersectCircleCircle(const Circle& c1, const Circle& c2){
	double x1, x2, y1, y2;
	int r1 = c1.radius, xc1 = c1.center.getx(), yc1 = c1.center.gety(),
		r2 = c2.radius, xc2 = c2.center.getx() - xc1, yc2 = c2.center.gety() - yc1;
	double A, B, C;
	A = -2 * xc2;
	B = -2 * yc2;
	C = pow(xc2 * 1., 2) + pow(yc2 * 1., 2) + pow(r1 * 1., 2) - pow(r2 * 1., 2);
	/*if (A == B && A == C && A == 0){
		return false;
	}*/
	if (r1 == r2 && 0 == xc2 && 0 == yc2){ 
		cout << "3";
		return true;
	}
	//C = A * xc1 + B * yc1 + C;
	//double d = pow(A * xc + B * yc + C, 2) / (A * A + B * B);
	//cout << r1 * r1 * (A * A + B * B) - pow(C, 2);
	//cout << distPointLineDoubles(xc1, yc1, A, B, C);
	double t = sqrt(r1 * r1 * (A * A + B * B) - pow(C, 2)) * 1. / (A * A + B * B);
	double x0 = (-A * C) * 1. / (A * A + B * B), y0 = (-B * C) * 1. / (A * A + B * B);
	if (length(xc1, xc2 + xc1, yc1, yc2 + yc1) < r1 + r2 && length(xc1, xc2 + xc1, yc1, yc2 + yc1) > myabs(r1 - r2)){
		x1 = x0 + B * t;
		x2 = x0 - B * t;
		y1 = y0 - A * t;
		y2 = y0 + A * t;
		printf("%s %s", "2", "\n");
		printf("%.5f %s %.5f %s", x1 + xc1, " ", y1 + yc1 , "\n");
		printf("%.5f %s %.5f %s", x2 + xc1, " ", y2 + yc1 , "\n");
	}
	else if (length(xc1, xc2 + xc1, yc1, yc2 + yc1) == r1 + r2 || length(xc1, xc2 + xc1, yc1, yc2 + yc1) == myabs(r1 - r2)){
		printf("%s %s", "1", "\n");
		printf("%.5f %s %.5f %s", x0 + xc1, " ", y0 + yc1, "\n");
	}
	else printf("%s", "0");
	return true;
}

bool convexPolygon(int n, const double* x, const double* y){
	Point* p = new Point[n];
	Vector temp1, temp2;
	bool rotRight = true, rotLeft = true;
	for (int i = 0; i < n; i++){
		p[i].x = x[i];
		p[i].y = y[i];
	}
	for (int i = 0; i < n; i++){
		temp1.beg = p[i];
		temp1.end = p[(i + 1) % n];
		temp2.beg = p[i];
		temp2.end = p[(i + 2) % n];
		//cout << rotdir(temp1, temp2) << endl; //
		if (rotdir(temp1, temp2) == 2) rotRight = false;
		else if(rotdir(temp1, temp2) == 1) rotLeft = false;
		else rotLeft = rotRight = false;
		//cout << rotLeft << " " << rotRight << endl; //
	}
	delete [] p;
	if (rotLeft == false && rotRight == false) return false;
	else return true;
}

bool pointInPolygon(int n, double xc, double yc, const double* x, const double* y){//	ищет кол-во пересечений луча напрвленного вправо из точки (xc, yc) со сторонами многоугольника. возвращает -1, если он лежит на ребре
	/*Point* p = new Point[n];
	Segment s;
	for (int i = 0; i < n; i++){
		p[i].x = x[i];
		p[i].y = y[i];
	}*/
	int counter = 0;
	Point p1, p2, c(xc, yc);
	Vector v1, v2;
	for (int i = 0; i < n; i++){
		p1.x = x[i];
		p1.y = y[i];
		p2.x = x[(i + 1) % n];
		p2.y = y[(i + 1) % n];
		v1.beg = p1;
		v1.end = c;
		v2.beg = p1;
		v2.end = p2;
		if (p1.gety() == yc && p1.getx() >= xc && (y[(i + n - 1) % n] <= yc && y[(i + 1) % n] >= yc || 
			y[(i + n - 1) % n] >= yc && y[(i + 1) % n] <= yc)) continue;
		if (((yc <= p2.gety() && yc >= p1.gety()) || (yc >= p2.gety() && yc <= p1.gety())) && 
			((xc <= p2.getx() && xc >= p1.getx()) || (xc >= p2.getx() && xc <= p1.getx())) && rotdir(v1, v2) == 0) return true;
		if (yc <= p2.gety() && yc >=p1.gety() && rotdir(v1, v2) == 1) counter++;// снизу вверх
		if (yc >= p2.gety() && yc <=p1.gety() && rotdir(v1, v2) == 2) counter++;// сверху вниз
		//cout << rotdir(v1, v2) << " " << counter << endl;
	}
	if (counter % 2 == 1) return true;
	else return false;
}

void Vector::containPoint(){
	int xa, ya, xb, yb, xc, yc;
	cin >> xc >> yc >> xa >> ya >> xb >> yb;
	Point a(xa, ya), b(xb, yb), c(xc, yc);
	Segment s(a, b);
	Vector v1(a, c);
	Vector v2(b, c);
	if (rotdir(v1, v2) == 0 && c.IfOnSegment(a, b) == true) cout << "YES";
	else cout << "NO";
}

void Vector::intersectSegmentFigure(){
	int xa, ya, xb, yb, xc, yc, xd, yd;
	cin >> xa >> ya >> xb >> yb >> xc >> yc >> xd >> yd;
	Point a(xa, ya), b(xb, yb), c(xc, yc), d(xd, yd);
	Segment s1(a, b), s2(c, d);
	if (intersect(s1, s2) == true) cout << "YES";
	else cout << "NO";
}

void Segment::containPoint(){
	int xa, ya, xb, yb, xc, yc;
	cin >> xc >> yc >> xa >> ya >> xb >> yb;
	Point a(xa, ya), b(xb, yb), c(xc, yc);
	Segment s(a, b);
	Vector v1(a, c);
	Vector v2(b, c);
	if (rotdir(v1, v2) == 0 && c.IfOnSegment(a, b) == true) cout << "YES";
	else cout << "NO";
}

void Segment::intersectSegmentFigure(){
	int xa, ya, xb, yb, xc, yc, xd, yd;
	cin >> xa >> ya >> xb >> yb >> xc >> yc >> xd >> yd;
	Point a(xa, ya), b(xb, yb), c(xc, yc), d(xd, yd);
	Segment s1(a, b), s2(c, d);
	if (intersect(s1, s2) == true) cout << "YES";
	else cout << "NO";
}

void Circle::containPoint(){
	int rad, xc, yc, x, y;
	cin >> xc >> yc >> rad;
	Point pc(xc, yc);
	Point p(x, y);
	Circle c(p, rad);
	if (length(p, pc) <= rad) cout << "YES";
	else cout << "NO";
}

void Circle::intersectSegmentFigure(){
	int xc, yc, r, A, B, C;
	cin >> xc >> yc >> r >> A >> B >> C;
	Point p(xc, yc);
	Circle c(p, r);
	cout.precision(10);
	if (intersectLineCircle(c, A, B, C));
	else cout << "0";
}

void Polygon::containPoint(){
	int n;
	double xc, yc;
	cin >> n >> xc >> yc;
	double* x = new double[n];
	double* y = new double[n];
	for (int i = 0; i < n; i++){
		fin >> x[i];
		fin >> y[i];
	}
	if (pointInPolygon(n, xc, yc, x, y)) cout << "YES";
	else cout << "NO";
	delete [] x;
	delete [] y;
}

void Polygon::intersectSegmentFigure(){
	int n;
	double xc, yc, x1, y1, x2, y2;
	cin >> n >> xc >> yc >> x1 >> y1 >> x2 >> y2;
	double* x = new double[n];
	double* y = new double[n];
	for (int i = 0; i < n; i++){
		cin >> x[i];
		cin >> y[i];
	}
	Segment s0(x1, y1, x2, y2);
	for (int i = 0; i < n; i++){
		Segment s1(x[i], y[i], x[(i + 1) % n], y[(i + 1) % n]);
		if (intersect(s1, s2) == true) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	delete [] x;
	delete [] y;
}
