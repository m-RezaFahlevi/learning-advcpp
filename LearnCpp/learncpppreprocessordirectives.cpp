// standard macro names
#include <bits/stdc++.h>
using namespace std;

int main(void) {
	cout << "This is the line number " << __LINE__;
	cout << " of file " << __FILE__ << ".\n";
	cout << "Its compilation began " << __DATE__;
	cout << " at " << __TIME__ << ".\n";
	cout << "The compiler gives a __cplusplus value of " << __cplusplus;
}
