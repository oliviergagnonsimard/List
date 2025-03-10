/**
* \ file list.h
* \ author Aida Ouangraoua (Fev 2025)
* \ brief Ce fichier contient les specifications du type list
*/


#ifndef list_h
#define list_h

#include <iostream>
#include <cassert>
//using namespace std;

/**
* \ brief Classe list
*/


template <typename TYPE>
class list{
  
 private:
  // definition du type cellule (encapsulation de chaque element)
  struct cellule{
    TYPE CONTENU;
    cellule *SUIV,*PREC;
    // constructeur de cellule
    cellule(const TYPE& C,cellule*S=nullptr,cellule*P=nullptr):CONTENU(C),SUIV(S),PREC(P){}
    // destructeur de cellule
    ~cellule(){PREC=SUIV=nullptr;}
  };
  cellule *DEBUT;
  size_t SIZE;
  
  //fonctions generatrices privees  
  cellule* insert(cellule*,const TYPE&); //insertion avant cette cellule 
  cellule* erase(cellule*); //retrait de cette cellule
  
 public:
  //classes d'iterateurs de listes
  class iterator;
  class reverse_iterator;

  //initialisation d'iterateurs
  iterator begin();
  iterator end();
  reverse_iterator rbegin();
  reverse_iterator rend(); 

  // constructeurs et destructeur
  list();
  list(size_t);
  list(std::initializer_list<TYPE>);
  list(list&);
  ~list();
  
  // permutation
  void swap(list&);
  //affectateur
  void operator=(list&);
  //changement de dimension
  void resize(size_t,const TYPE& = TYPE());
  void splice(iterator,list&);
  // liberation de l'espace memoire
  void clear();

  //ajout d'element a une position
  iterator insert(iterator,const TYPE&);
  reverse_iterator insert(reverse_iterator,const TYPE&); 
  //retrait d'un element
  iterator erase(iterator);
  reverse_iterator erase(reverse_iterator);
  
  //ajout d'element a la fin
  void push_back(const TYPE&);
  //retrait du dernier element
  void pop_back();
  //ajout d'element au debut
  void push_front(const TYPE&);
  //retrait du premier element
  void pop_front();
  
  //selecteur : taille
  size_t size()const;
  //selecteur : est vide ?
  bool empty()const;
  //selecteur : dernier element
  TYPE& back();
  //selecteur const : dernier element
  const TYPE& back()const;
  //selecteur : premier element
  TYPE& front();
  //selecteur const : premier element
  const TYPE& front()const;
  
  
  //inversion de la liste
  void reverse();
  //tri de la liste
  void sort(iterator,iterator);
  
  //affichage
  void afficher()const;
};



template <typename TYPE>
class list<TYPE>::iterator{
  friend class list<TYPE>;
 private:
    cellule* POINTEUR;
public:
    iterator(cellule*C=nullptr):POINTEUR(C){}
    TYPE& operator*()const{return POINTEUR->CONTENU;} //*i
    TYPE* operator->()const{return &(POINTEUR->CONTENU);} //i->
    iterator& operator++(){POINTEUR=POINTEUR->SUIV;return *this;} //++i
    iterator operator++(int){iterator it(*this); POINTEUR=POINTEUR->SUIV; return it;} //i++
    iterator& operator--(){POINTEUR=POINTEUR->PREC;return *this;} //--i
    iterator operator--(int){iterator ret(*this);POINTEUR=POINTEUR->PREC;return ret;} //i--  
    bool operator==(const iterator& IT)const{
        return POINTEUR==IT.POINTEUR;}
    bool operator!=(const iterator& IT)const{
        return POINTEUR!= IT.POINTEUR;}
};


template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::begin(){
  return iterator(DEBUT->SUIV);
}

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::end(){
  return iterator(DEBUT->PREC);
}


template <typename TYPE>
list<TYPE>::list():SIZE(0){
  cellule* fin = new cellule(TYPE());
  DEBUT = new cellule(TYPE(),fin,fin);
  fin->PREC = DEBUT;  
}
	
template <typename TYPE>
list<TYPE>::list(size_t N):list(){
  for(size_t  i = 0; i < N; i++)  push_back(TYPE());
}

template <typename TYPE>
list<TYPE>::list(std::initializer_list<TYPE> L):list(){
  for(const TYPE & x:L) push_back(x);
}

template <typename TYPE>
list<TYPE>::list(list& L):list(){
  *this=L;
}

template <typename TYPE>
list<TYPE>::~list(){
  clear();
  delete(DEBUT->PREC);
  delete(DEBUT);
}

template <typename TYPE>
void list<TYPE>::swap(list& L){
  std::swap(DEBUT, L.DEBUT);
  std::swap(SIZE, L.SIZE);
}
  

template <typename TYPE>
void list<TYPE>::clear(){
  list<TYPE>::iterator it = begin();
  while(it != end()) it=erase(it);  
}

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::insert(iterator i,const TYPE& x){
  return iterator(insert(i.POINTEUR,x));
}

template <typename TYPE>
typename list<TYPE>::iterator list<TYPE>::erase(iterator i){
  return iterator(erase(i.POINTEUR));
}

template <typename TYPE>
void list<TYPE>::push_back(const TYPE& x){
  insert(end(),x);
}

template <typename TYPE>
void list<TYPE>::pop_back(){
  erase(rbegin());
}

template <typename TYPE>
void list<TYPE>::push_front(const TYPE& x){
  insert(begin(),x);
}

template <typename TYPE>
void list<TYPE>::pop_front(){
  erase(begin());
}

template <typename TYPE>
size_t list<TYPE>::size()const{
  return SIZE;
}

template <typename TYPE>
bool list<TYPE>::empty()const{
  return SIZE==0;
}

template <typename TYPE>
const TYPE& list<TYPE>::back()const{
  return *rbegin();
}

template <typename TYPE>
const TYPE& list<TYPE>::front()const{
  return *begin();
}

template <typename TYPE>
TYPE& list<TYPE>::back(){
  return *rbegin();
}

template <typename TYPE>
TYPE& list<TYPE>::front(){
  return *begin();
}

template <typename TYPE>
void list<TYPE>::afficher()const{
  size_t n = size();
  std::cout << std::endl << "SIZE: " << n  << std::endl;
  
  cellule* deb=DEBUT;
  cellule* fin=deb->PREC;
  //forward
  std::cout << "forward" << std::endl;
  char delim = '{';
  if(n== 0)
    std::cout << delim;
  cellule* c=deb->SUIV;
  while(c != fin){
    std::cout << delim << c->CONTENU;
    delim = ',';
    c = c ->SUIV;
      }
  std::cout << "}"<< std::endl;
  //reverse
  std::cout << "reverse" << std::endl;
  delim = '{';
  if(n== 0)
    std::cout << delim;
  c=fin->PREC;
  while(c != deb){
    std::cout << delim << c->CONTENU;
    delim = ',';
    c = c ->PREC;
      }
  std::cout << "}"<< std::endl;
}

//Inclusion de list2.h
#include "list2.h"

#endif
