// typeid, polymorphic class
#include <bits/stdc++.h>
using namespace std;

class CBase {
	virtual void f() {};
};

class CDerived: public CBase {};

int main(void) {
	try {
		CBase *a = new CBase;
		CBase *b = new CDerived;
		cout << "a is: " << typeid(a).name() << endl;
		cout << "b is: " << typeid(b).name() << endl;
		cout << "*a is : " << typeid(*a).name() << endl;
		cout << "*b is : " << typeid(*b).name() << endl;
	} catch (exception &e) {
		cout << "Exception : " << e.what() << endl;
	}
}
