#include "list.h"

#include <iostream>

using namespace std;

int main() {

	list<int> shish;

	shish.push_front(5);
	shish.push_front(6);
	shish.push_front(7);
	shish.push_front(8);


	shish.afficher();

	shish.pop_front();

	shish.afficher();

	cout << "Bhay" << endl;

	return 0;
}