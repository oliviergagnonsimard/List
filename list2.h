/**
* \ file: list2.h
* \ authors:
	Olivier Gagnon-Simard, CIP: gago0665
	Jean-Cristoph Larue, CIP: larj
* \ brief: Ce fichier contient les fonctions du type list à coder
*/

#ifndef list2_h
#define list2_h

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

template <typename TYPE>
typename list<TYPE>::cellule* list<TYPE>::erase(cellule* C) {
	C->PREC->SUIV = C->SUIV;

	if (C != DEBUT->PREC)
		C->SUIV->PREC = C->PREC;

	SIZE--;

	return C;
}


// 3 pts
template <typename TYPE>
class list<TYPE>::reverse_iterator {
	friend class list<TYPE>;
private:
	cellule* POINTEUR;
public:
	reverse_iterator(cellule* C = nullptr) :POINTEUR(C) {}
	TYPE& operator*()const { return POINTEUR->CONTENU; } //*i
	TYPE* operator->()const { return &(POINTEUR->CONTENU); } //i->
	iterator& operator++() { POINTEUR = POINTEUR->PREC; return *this; } //++i
	iterator operator++(int) { iterator it(*this); POINTEUR = POINTEUR->PREC; return it; } //i++
	iterator& operator--() { POINTEUR = POINTEUR->SUIV; return *this; } //--i
	iterator operator--(int) { iterator ret(*this); POINTEUR = POINTEUR->SUIV; return ret; } //i--  
	bool operator==(const iterator& IT)const {
		return POINTEUR == IT.POINTEUR;
	}
	bool operator!=(const iterator& IT)const {
		return POINTEUR != IT.POINTEUR;
	}
};

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rbegin() {
	// DEBUT -> QUEUE -> DERNIER ÉLÉMENT
	return reverse_iterator(DEBUT->PREC->PREC);
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::rend() {
	return reverse_iterator(DEBUT->SUIV);
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::insert(reverse_iterator i, const TYPE& x) {
	/*... a effacer et completer ...*/
	return reverse_iterator();
}

template <typename TYPE>
typename list<TYPE>::reverse_iterator list<TYPE>::erase(reverse_iterator i) {
	/*... a effacer et completer ...*/
	return reverse_iterator();
}

template <typename TYPE>
void list<TYPE>::operator=(list<TYPE>& L) {
	// Si les listes ne sont pas de la même longueur, on ne fait rien.
	if (SIZE != L.SIZE)
		throw std::exception("Listes pas de la même longueur!");

	cellule* c = DEBUT->SUIV;
	cellule* l = L.DEBUT->SUIV;

	for (int i = 0; i < SIZE; i++) {
		c->CONTENU = l->CONTENU;
		c = c->SUIV;
		l = l->SUIV;
	}
}

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
	/*... a completer ...*/
}

template <typename TYPE>
void list<TYPE>::reverse() {
	//DEBUT->PREC->SUIV = DEBUT->PREC->SUIV->PREC;
	//DEBUT->PREC = nullptr;

	cellule* cell;
	for (int i = 0; i < SIZE; i++) {
		cell = DEBUT->SUIV; // on avance dans la liste 
		std::swap(cell->PREC, cell->SUIV); // on échange les pointeurs
	}
}

template <typename TYPE>
void list<TYPE>::sort(iterator DEB, iterator FIN) {
	/*... a completer ...*/
}

#endif
