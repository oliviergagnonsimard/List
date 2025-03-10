#include "list.h"

#include <iostream>

using namespace std;

void main() {

	list<int> shish;


	shish.push_front(5);
	int taille = shish.size();

	shish.afficher();
}