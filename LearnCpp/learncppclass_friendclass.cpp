#include <bits/stdc++.h>
using namespace std;

class CSquare;

class CRectangle {
	int width, height;
	public:
		int area() {return width* height;}
		void convert(CSquare a);
};

class CSquare {
	private:
		int side;
	public:
		void set_side(int a) {side = a;}
		friend class CRectangle;
};

void CRectangle::convert(CSquare a) {
	width = a.side;
	height = a.side;
}

int main(void) {
	CSquare sqr;
	CRectangle rect;
	sqr.set_side(4);
	rect.convert(sqr);
	cout << rect.area();
}
