// thread example
#include <bits/stdc++.h>
using namespace std;

void foo(void) {
	for (int i = 0; i < 10; ++i)
		cout << "Bidoof ";
	cout << endl;
}

void bar(int x) {
	for (int i = 0; i < 10; ++i)
		cout << x << " ";
	cout << endl;
}

int main(void) {
	thread first(foo);
	thread second(bar, 0);

	cout << "main, foo, and bar now execute concurrently.." << endl;

	// synchronize threads:
	first.join();
	second.join();

	cout << "foo and bar completed" << endl;
}
