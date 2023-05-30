// constructors and derived classes
#include <bits/stdc++.h>
using namespace std;

class mother {
	public:
		mother();
		mother(int);
};

mother::mother() {
	cout << "mother: no paramters\n";
}

mother::mother(int a) {
	cout << "mother: int parameters\n";
}

class daughter:public mother {
	public:
		daughter(int);
};

daughter::daughter(int a) {
	cout << "daughter: int parameter\n\n";
}

class son:public mother {
	public:
		son(int a):mother(a) {
			cout << "son: int parameter\n\n";
		}
};

int main(void) {
	daughter cynthia(0);
	son daniel(0);
}
