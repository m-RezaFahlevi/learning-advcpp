 // function template II
 #include <bits/stdc++.h>
 using namespace std;

 template <class MetaType>
 MetaType GetMax(MetaType a, MetaType b) {
 	return (a > b ? a : b);
 }

template <class MetaTypeT, class MetaTypeU>
MetaTypeT GetMax2(MetaTypeT a, MetaTypeU b) {
	return (a > b ? a : b);
}


 int main(void) {
 	int i = 5, j = 6, k;
	long l = 19, m = 5, n;
	k = GetMax(i, j);
	n = GetMax(l, m);
	m = GetMax2(j, l);
	cout << k << endl;
	cout << n << endl;
	cout << m << endl;
 }
