#pragma once
class Segment;
class Circle;

class Metrics2D{
public:
	virtual void containPoint(){};
	virtual void intersectSegmentFigure(){};
};

class Point: public Metrics2D{
protected:
	/*int x;
	int y;*/
	double x;
	double y;
public:
	Point();
	Point(int, int);
	Point(const Point&);
	Point& operator = (const Point&);
	friend Point operator - (const Point&, const Point&);
	friend Point operator + (const Point&, const Point&);
	int getx(){return x;}
	int gety(){return y;}
	const int getx() const {return x;}
	const int gety() const {return y;}
	void set(int, int);
	bool belongsToAngle(const Point& a, const Point& b, const Point& o); // ��������� �������������� ������ ����� ���� AOB
	bool IfOnSegment(const Point& a, const Point& b); // �������� �������������� ����� �������, ����
	const bool IfOnSegment(const Point& a, const Point& b) const; // ��������, ��� ��� ����� �� ������, ���������� �������
	bool belongsToSegment(const Segment& s);
	friend double distPointSegment(const Point&, const Segment&);
	friend double length(const Point&, const Point&);
	friend bool convexPolygon(int n, const double* x, const double* y);
	friend bool pointInPolygon(int n, double xc, double yc, const double* x, const double* y);
};

class Vector: public Metrics2D{ // ������ Vector �� ������������ �������
protected:
	Point beg;
	Point end;
public:
	Vector(int, int, int, int);
	Vector(const Point&, const Point&);
	Vector(const Vector& obj);
	friend int vectmult(const Vector&, const Vector&); // ��������� ������������
	friend int rotdir(const Vector& v1, const Vector& v2); // ���������� ����������� �������� �� v1 �  v2
	friend bool convexPolygon(int n, const double* x, const double* y);
	friend bool pointInPolygon(int n, double xc, double yc, const double* x, const double* y);
	void containPoint();
	void intersectSegmentFigure();
};

class Segment: public Metrics2D{
protected:
	Point p1;
	Point p2;
public:
	Segment(int, int, int, int);
	Segment(const Point&, const Point&);
	Segment(const Segment& obj);
	friend bool intersect(const Segment&, const Segment&);
	friend double distPointLine(const Point&, const Segment&);
	friend double distPointSegment(const Point&, const Segment&);
	friend bool Point::belongsToSegment(const Segment& s);
	double length();
	const double length() const;
	void containPoint();
	void intersectSegmentFigure();
};

class Circle: public Metrics2D{
protected:
	Point center;
	int radius;
public:
	Circle();
	Circle(const Point&, int);
	Circle(const Circle&);
	friend bool intersectLineCircle(const Circle&, double, double, double);
	friend bool intersectCircleCircle(const Circle&, const Circle&);
	void containPoint();
	void intersectSegmentFigure();
};

class Polygon: public Metrics2D{
	void containPoint();
	void intersectSegmentFigure();
};