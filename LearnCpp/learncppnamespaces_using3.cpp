// using namespace example
#include <bits/stdc++.h>
using namespace std;

namespace first {
	int x = 5;
}

namespace second {
	double x = 3.1416;
}

int main(void) {
	{ using namespace first;
		cout << x << endl;
	} { using namespace second;
		cout << x << endl;
	}
}
