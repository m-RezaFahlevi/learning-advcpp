// function macro
#include <bits/stdc++.h>
#define getmax(a, b) ((a) > (b) ? a : b)
using namespace std;

int main(void) {
	int x = 5, y;
	y = getmax(x, 2);
	cout << y << endl;
	cout << getmax(7, x) << endl;
}
