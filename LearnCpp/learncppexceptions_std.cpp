// standard exceptions
#include <bits/stdc++.h>
using namespace std;

class myexception: public exception {
	virtual const char *what () const throw() {
		return "My exception happended";
	}
};

int main(void) {
	myexception myex;
	try {
		throw myex;
	} catch(exception &e) {
		cout << e.what() << endl;
	}
}
