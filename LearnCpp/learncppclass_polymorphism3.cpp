// abstract base class
#include <bits/stdc++.h>
using namespace std;

class CPolygon {
	protected:
		int width, height;
	public:
		void set_values(int, int);
		virtual int area(void) = 0;
};

void CPolygon::set_values(int a, int b) {
	width = a;
	height = b;
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
	CRectangle rect;
	CTriangle trgl;
	CPolygon *ppoly1 = &rect;
	CPolygon *ppoly2 = &trgl;
	ppoly1->set_values(4, 5);
	ppoly2->set_values(4, 5);
	cout << ppoly1->area() << endl;
	cout << ppoly2->area() << endl;
}
