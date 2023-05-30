// class type-casting
#include <bits/stdc++.h>
using namespace std;

class CDummy{
	float i, j;
};

class CAddition {
	int x, y;
	public:
		CAddition(int, int);
		int result();
};

CAddition::CAddition(int a, int b) {
	x = a;
	y = b;
}

int CAddition::result() {
	return x + y;
}

int main(void) {
	CDummy d;
	CAddition *padd;
	padd = (CAddition *) &d;
	cout << padd->result();
}
