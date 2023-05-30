// example about structures
#include <bits/stdc++.h>
using namespace std;

struct movies_t {
	string title;
	int year;
} mine, yours;

void printmovie(movies_t movie) {
	cout << movie.title;
	cout << " (" << movie.year << ")\n";
}

int main(void) {
	string mystr;

	mine.title = "2001 A Space Odyssey";
	mine.year = 1968;

	cout << "Enter title: ";
	getline(cin, yours.title);
	cout << "Enter year: ";
	getline(cin, mystr);
	stringstream(mystr) >> yours.year;

	cout << "My favorite movie is:\n";
	printmovie(mine);
	cout << "And yours is:\n";
	printmovie(yours);
}
