// pointer to functions
#include <bits/stdc++.h>
using namespace std;

int addition(int a, int b) {return a + b;}

int substraction(int a, int b) {return a - b;}

int operation(int x, int y, int (*functocall)(int, int)) {
	int g;
	g = (*functocall)(x, y);
	return g;
}

int main(void) {
	int m, n;
	int (*minus)(int, int) = substraction;

	m = operation(7, 5, addition);
	n = operation(20, m, minus);
	cout << n << endl;
}
