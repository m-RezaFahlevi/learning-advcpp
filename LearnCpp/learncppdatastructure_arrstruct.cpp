// array of structures
#include <bits/stdc++.h>
#define N_MOVIES 3
using namespace std;

struct movies_t {
	string title;
	int year;
} films[N_MOVIES];

void printmovie(movies_t movie) {
	cout << movie.title;
	cout << " (" << movie.year << ")\n";
}

int main(void) {
	string mystr;
	int n;

	for (n = 0; n < N_MOVIES; n++) {
		cout << "Enter title: ";
		getline(cin, films[n].title);
		cout << "Enter year: ";
		getline(cin, mystr);
		stringstream(mystr) >> films[n].year;
	}

	cout << "\nYou have entered these movies:\n";
	for (n = 0; n < N_MOVIES; n++)
		printmovie(films[n]);
}
