// sequence template
#include <bits/stdc++.h>
using namespace std;

template <class GenType, int N>
class mysequence {
	GenType memblock[N];
	public:
		void setmember(int x, GenType value);
		GenType getmember(int x);
};

template <class GenType, int N>
void mysequence<GenType, N>::setmember(int x, GenType value) {
	memblock[x] = value;
}

template <class GenType, int N>
GenType mysequence<GenType, N>::getmember(int x) {
	return memblock[x];
}

int main(void) {
	mysequence<int, 5> myints;
	mysequence<double, 5> myfloats;
	myints.setmember(0, 100);
	myfloats.setmember(3, 3.1416);
	cout << myints.getmember(0) << endl;
	cout << myints.getmember(1) << endl;
	cout << myfloats.getmember(3) << endl;
}
