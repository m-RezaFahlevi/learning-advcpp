// class templates
#include <bits/stdc++.h>
using namespace std;

template <class MetaType>
class mypair {
	MetaType a, b;
	public:
		mypair(MetaType first, MetaType second);
		MetaType getmax();
};

template <class MetaType>
mypair<MetaType>::mypair(MetaType first, MetaType second) {
	a = first;
	b = second;
}

template <class MetaType>
MetaType mypair<MetaType>::getmax() {
	MetaType retval;
	retval = a > b ? a : b;
	return retval;
}

int main(void) {
	mypair<int> myobject(100, 75);
	cout << myobject.getmax();
}
