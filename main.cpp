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

	cout << "----- INSERT ET ERASE ------" << endl;
	shish.afficher();

	shish.insert(shish.begin(), 19);
	shish.insert(shish.end(), 21);

	// Cas limite! (Effacer � la fin et probablement ajouter � la fin)
	//shish.erase(shish.end());


	shish.afficher();

	/* Test du operator= */
	cout << "----- OPERATOR= ------" << endl;

	shish2.push_front(5);
	shish2.push_front(6);
	shish2.push_front(7);
	shish2.push_front(8);
	shish2.push_front(9);
	shish2.push_front(10);

	shish = shish2;
	shish.afficher();

	/* Test du resize */
	//cout << "----- RESIZE ------" << endl;

	//shish.resize(3);
	//shish.afficher();

	/* Test du reverse */
	cout << "----- REVERSE ------" << endl;

	list<int> shish3; // liste impaire

	shish3.push_front(5);
	shish3.push_front(6);
	shish3.push_front(7);
	shish3.push_front(8);
	shish3.push_front(9);

	cout << "AVANT: " << endl;
	shish3.afficher();
	cout << "===" << endl;
	shish3.reverse();
	cout << "APRES: " << endl;
	shish3.afficher();

	/* Test du sort */
	cout << "----- SORT ------" << endl;

	shish.sort(shish.begin(), shish.end());
	shish.afficher();


	cout << endl;

	cout << "Doudous chiches" << endl;

	return 0;
}