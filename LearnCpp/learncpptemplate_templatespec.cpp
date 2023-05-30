// template specialization
#include <bits/stdc++.h>
using namespace std;

// class template:
template <class GenType> // GenType stand for Generic Type
class mycontainer {
	GenType element;
	public:
		mycontainer(GenType arg);
		GenType increase();
};

template <class GenType>
mycontainer<GenType>::mycontainer(GenType arg) {
	element = arg;
}

template <class GenType>
GenType mycontainer<GenType>::increase() {
	return ++element;
}

// class template specialization:
template <>
class mycontainer<char> {
	char element;
	public:
		mycontainer(char arg);
		char uppercase();
};

mycontainer<char>::mycontainer(char arg) {
	element = arg;
}

char mycontainer<char>::uppercase() {
	if ((element >= 'a') && (element <= 'z'))
		element += 'A' - 'a';
	return element;
}

int main(void) {
	mycontainer<int> myint(7);
	mycontainer<char> mychar('j');
	cout << myint.increase() << endl;
	cout << mychar.uppercase() << endl;
}
