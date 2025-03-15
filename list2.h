/**
**********************************************************************
* \ file: list2.h
* \ authors:
	Olivier Gagnon-Simard, CIP: gago0665
	Jean-Cristoph Larue, CIP: larj0665
* \ brief: Ce fichier contient les fonctions du type list à coder
**********************************************************************
*/

#ifndef list2_h
#define list2_h

/*
Fonction: insert
Param: cellule*, const TYPE&
Retour: cellule*
Description: Nous insérons dans la fonction une cellule et un index et nous déplaçons
toutes les cellules d'une case vers la droite et plaçons la nouvelle cellule à la valeur X dans
l'endroit vide libéré et déplaçons les pointeurs précédants et suivants à la cellule ajoutée.
*/
template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::insert(cellule* C, const TYPE& X) {
	cellule* cell = new cellule(X);

	cell->SUIV = C;
	cell->PREC = C->PREC;

	C->PREC = cell;
	cell->PREC->SUIV = cell;

	SIZE++;

	return cell;
}

/*
Fonction: erase
Param: cellule*
Retour: cellule*
Description: Nous insérons la cellule à supprimer dans la fonction et déplaçons les pointeurs
qui sont précédents et suivants à la cellule dans la list.
*/
template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::erase(cellule* C) {
	C->PREC->SUIV = C->SUIV;

	if (C != DEBUT->PREC)
		C->SUIV->PREC = C->PREC;

	SIZE--;

	return C;
}


/*
Class: reverse_iterator
Description: Permet d'itérer dans la liste à partir de la fin vers le début.
Ressemble énormément à la classe iterator normale, mais nous inversons les
operator++ et operator--, nous faisons ça afin que lorsque nous avançons dans la liste
nous faisons un PREC dans les pointeurs au lieu d'un SUIV pour itérer à l'envers.
*/
template <typename TYPE>
class list<TYPE>::reverse_iterator {
	friend class list<TYPE>;
private:
	cellule* POINTEUR;
public:
	reverse_iterator(cellule* C = nullptr) :POINTEUR(C) {}
	TYPE& operator*()const { return POINTEUR->CONTENU; } //*i
	TYPE* operator->()const { return &(POINTEUR->CONTENU); } //i->
	reverse_iterator& operator++() { POINTEUR = POINTEUR->PREC; return *this; } //++i
	reverse_iterator operator++(int) { reverse_iterator it(*this); POINTEUR = POINTEUR->PREC; return it; } //i++
	reverse_iterator& operator--() { POINTEUR = POINTEUR->SUIV; return *this; } //--i
	reverse_iterator operator--(int) { reverse_iterator ret(*this); POINTEUR = POINTEUR->SUIV; return ret; } //i--  
	bool operator==(const reverse_iterator& IT)const {
		return POINTEUR == IT.POINTEUR;
	}
	bool operator!=(const reverse_iterator& IT)const {
		return POINTEUR != IT.POINTEUR;
	}
};

/*
Fonction: rbegin
Param:
Retour: reverse_iterator
Description: Nous retournons un reverse_iterator avec comme cellule de début la fin de la liste
en faisant précédant de DÉBUT ce qui nous donne la QUEUE
et précédent de QUEUE qui nous donne le dernier élément de la liste.
*/
template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rbegin() {
	// DEBUT -> QUEUE -> DERNIER ÉLÉMENT
	return reverse_iterator(DEBUT->PREC->PREC);
}

/*
Fonction: rend
Param:
Retour: reverse_iterator
Description: Puisque l'iterator comme à la fin et que cette fonction doit retourner la fin d'un reverse_iterator,
alors nous retournons le premier élément de la liste en faisant un suivant de DÉBUT.
*/
template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rend() {
	return reverse_iterator(DEBUT->SUIV);
}

/*
Fonction: insert
Param: reverse_iterator, const TYPE&
Retour: reverse_iterator
Description: Nous insérons dans la liste avec le reverse_iterator à partir de la fin vers le début.
*/
template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::insert(reverse_iterator i, const TYPE& x) {
	cellule* cell = i.POINTEUR; // cellule où insérer
	cell->CONTENU = x;

	cellule* cellActuelle = DEBUT->PREC->PREC; // Dernier élément

	for (int j = 0; j < SIZE; j++) {
		if (cell == cellActuelle) {
			cell->SUIV = cellActuelle;
			cell->PREC = cellActuelle.PREC;
			break;
		}
		cellActuelle = cellActuelle->PREC; // On avance dans la liste
	}

	return reverse_iterator();
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::erase(reverse_iterator i) {
	cellule* cell = i.POINTEUR;
	cellule* c;
	reverse_iterator rv_it(DEBUT->PREC->PREC);

	for (int j = 0; j < SIZE; j++) {
		if (rv_it.POINTEUR == cell) {
			c = rv_it.POINTEUR;
			c->PREC->SUIV = c->SUIV;
			c->SUIV->PREC = c->PREC;
			delete c;
			break;
		}
		rv_it++;
	}


	return reverse_iterator();
}

/*
Fonction: operator=
Param: list<TYPE>&
Retour:
Description: Nous parcourons chaque élément de la liste et nous remplaçons chaque élément
par l'élément à la même position (index) de la liste passée en paramètre.
*/
template <typename TYPE>
void list<TYPE>::operator=(list<TYPE>& L) {
	// Si les listes ne sont pas de la même longueur, on ne fait rien.
	if (SIZE != L.SIZE)
		throw std::exception("Listes pas de la même longueur!");


	cellule* c = DEBUT->SUIV;
	cellule* l = L.DEBUT->SUIV;

	// On change chaque valeur de notre liste pour celle passée en paramètre
	for (int i = 0; i < SIZE; i++) {
		c->CONTENU = l->CONTENU;
		c = c->SUIV;
		l = l->SUIV;
	}
}

/*
Fonction: resize
Param: size_t, const TYPE& X
Retour:
Description: Si N est plus grand que la taille de la liste, nous augmentons la liste à la taille N et remplissons
les éléments manquants par la valeur X passée en paramètre. Si N est plus petit que la taille de la liste, nous enlevons
les éléments de la liste après N en changeant le SUIV à l'endroit N à nullptr
*/
template <typename TYPE>
void list<TYPE>::resize(size_t N, const TYPE& X) {
	int surplus;
	if (N > SIZE) {
		surplus = N - SIZE;

		for (int i = 0; i < surplus; i++)
			push_back(X);

		return;
	}

	surplus = SIZE - N;

	for (int i = 0; i < surplus; i++)
		pop_back();
}

template <typename TYPE>
void list<TYPE>::splice(iterator i, list& L) {
	cellule* newCell(L.DEBUT); // Le début de la liste L
	cellule* cell = i.POINTEUR; // Cellule ou on insère la liste L
	cellule* new_cellFin = newCell->PREC->PREC; // Dernier élément de la liste L

	// Le suivant du précédent à de la cellule à laquelle qu'on insère L devient: le premier élément de la liste L
	cell->PREC->SUIV = newCell->SUIV;

	// L'endroit où à été inséré la nouvelle liste a comme précédent: la fin de la la liste L
	cell->PREC = new_cellFin;
	i++;
	cell->SUIV = i.POINTEUR;

	// Le prochain élément du dernier élément de la liste L devient cell (où a été inséré la liste à la base)
	new_cellFin->SUIV = cell;

	L.SIZE = 0; // on change le size de L à 0 sans supprimer ses valeurs
}


/*
Fonction: reverse
Param:
Retour:
Description: Nous devons inverser la liste, donc tous les éléments sont inversés. C'est-à-dire, que nous commençons
de la fin en allant au début et interchangeons les éléments à l'endroit (i) et à l'endroit (SIZE-i).
*/
template <typename TYPE>
void list<TYPE>::reverse() {
	// Si la liste n'a pas de tête ou est vide, alors on ne fait rien
	if (DEBUT == nullptr || DEBUT->SUIV == nullptr)
		return;

	cellule* tete = DEBUT;
	cellule* queue = DEBUT->PREC;

	cellule* cellNormal;
	cellule* cellReverse;

	iterator normal(tete->SUIV);
	reverse_iterator reverse(queue->PREC);

	/*
	Lorsque la taille est paire ex: [1, 2, 3, 4, 5, 6]; on doit faire 3 swaps donc (SIZE / 2 = 3, donc 3 swaps)
	mais lorsque c'est impair, ex: [1, 2, 3, 4, 5]; on doit faire 2 swaps seulement (SIZE / 2 = 2, donc 2 swaps)

	*** DIVISION ENTIÈRE DONC 5 / 2 = 2 ***
	*/
	int taille = SIZE / 2;

	for (int i = 0; i < taille; i++) {
		cellNormal = normal.POINTEUR; // cellule actuelle sens normal
		cellReverse = reverse.POINTEUR; // cellule actuelle sens inverse


		std::swap(cellNormal->CONTENU, cellReverse->CONTENU);

		normal++; // on fait un SUIV sur l'itérateur dans le sens normal
		reverse++; // on fait un SUIV sur l'itérateur dans le sens inverse (donc un PREC)
	}
}

/*
Fonction: sort
Param: iterator, iterator
Retour:
Description: Nous devons classer en ordre croissant les éléments de la liste, donc pour chaque valeur actuelle
si une valeur après celle-ci dans le reste de la liste est plus petite, nous les swappons.
Une spécificité de la fonction est que dans nous pouvons sort seulement une sous-section de la liste en insérant les cellules appropriées.
*/
template <typename TYPE>
void list<TYPE>::sort(iterator DEB, iterator FIN) {
	cellule* currentCell = DEB.POINTEUR; // Cellule où on commence à sort (au début)
	cellule* comparedCell; // Cellule qu'on compare à cell
	cellule* lastCell = FIN.POINTEUR->PREC; // Dernière cellule qu'on sort


	// Si on pointe vers la même cellule, on fait rien
	if (DEB.POINTEUR == FIN.POINTEUR)
		return;

	while(currentCell != lastCell) {
		currentCell = DEB.POINTEUR;
		comparedCell = currentCell->SUIV;
		iterator comparateur(comparedCell);

		while (comparedCell->SUIV != nullptr) {


			if (comparedCell->CONTENU < currentCell->CONTENU) {
				std::swap(comparedCell->CONTENU, currentCell->CONTENU);
			}

			comparateur++;
			comparedCell = comparateur.POINTEUR;
		}

		DEB++;
	}

}

// SIZE=7, i = 0, SIZE-(0+1) = 6
// 4 5 6 13 4 9 0
// i = 1, SIZE-(1+1) = 5
// 0 4 5 6 13 4 9
// 0 4 4 5 6 13 9
// 0 4 4 5 6 9 13

#endif
