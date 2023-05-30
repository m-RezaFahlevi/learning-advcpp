// dynamic allocation and polymorphism
#include <bits/stdc++.h>
using namespace std;

class CPolygon {
	protected:
		int width, height;
	public:
		void set_values(int, int);
		virtual ~CPolygon() =default; // virtual destructor
		virtual int area(void) =0;
		void printarea(void);
};

void CPolygon::set_values(int a, int b) {
	width = a;
	height = b;
}

void CPolygon::printarea(void) {
	cout << this->area() << endl;
}

class CRectangle: public CPolygon {
	public:
		int area(void);
};

int CRectangle::area(void) {
	return width * height;
}

class CTriangle: public CPolygon {
	public:
		int area(void);
};

int CTriangle::area(void) {
	return width * height / 2;
}

int main(void) {
	CPolygon *ppoly1 = new CRectangle;
	CPolygon *ppoly2 = new CTriangle;
	ppoly1->set_values(4, 5);
	ppoly2->set_values(4, 5);
	ppoly1->printarea();
	ppoly2->printarea();
	delete ppoly1;
	delete ppoly2;
}
