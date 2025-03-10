#include "list.h"

#include <iostream>

using namespace std;

int main() {

	list<int> shish;
	list<int> shish2;

	/* Test du insert et erase */
	shish.push_front(1);
	shish.push_front(2);
	shish.push_front(3);
	shish.push_front(4);

	shish.afficher();

	shish.insert(shish.begin(), 19);
	shish.insert(shish.end(), 21);

	// Cas limite! (Effacer à la fin et probablement ajouter à la fin)
	//shish.erase(shish.end());


	shish.afficher();

	/* Test du operator= */
	shish2.push_front(5);
	shish2.push_front(6);
	shish2.push_front(7);
	shish2.push_front(8);
	shish2.push_front(9);
	shish2.push_front(10);

	shish = shish2;
	shish.afficher();

	/* Test du resize */
	shish.resize(3);
	shish.afficher();


	cout << endl;

	cout << "Doudous chiches" << endl;

	return 0;
}