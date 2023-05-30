// pointers to structures
#include <bits/stdc++.h>
using namespace std;

struct movies_t {
	string title;
	int year;
};

struct friends_t {
	string name;
	string email;
	movies_t favorite_movie;
} charlie, maria;

int main(void) {
	friends_t *pfriends = &charlie;
	charlie.name = "Charlie";
	maria.favorite_movie.title = "Bidoof";
	charlie.favorite_movie.year = 2009;
	cout << pfriends->favorite_movie.year;
}
