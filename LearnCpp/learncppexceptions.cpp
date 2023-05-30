// exceptions
#include <bits/stdc++.h>
using namespace std;

int main(void) {
	try {
		throw 20;
	} catch(int param) {
		cout << "int exception";
	} catch(char param) {
		cout << "char exception";
	} catch (...) {
		cout << "default exception";
	}
}
