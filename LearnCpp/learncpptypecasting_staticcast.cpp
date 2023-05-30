// static casting
#include <bits/stdc++.h>
using namespace std;

class CBase {
	virtual void dummy() {};
};

class CDerived: public CBase {
	int a;
};

int main(void) {
	try {
		CBase *pba = new CDerived;
		CBase *pbb = new CBase;

		CBase *a = new CBase;
		if (a == nullptr)
			cout << "Null pointer on first type-cast" << endl;

		CDerived *b = static_cast<CDerived *>(a);
		if (b == nullptr)
			cout << "Null pointer on second type-cast" << endl;
	} catch (exception &e) {
		cout << "Exception: " << e.what();
	}
}
