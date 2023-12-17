#ifndef DRAWPILE_H
#define DRAWPILE_H

#include "Card.h"

#include<iostream>
using namespace std;

class DrawPile {
public:
	DrawPile(size_t taille): taille(taille) {
		pile = new Card*[taille];
		for (int i = 0; i < taille; i++) pile[i] = nullptr;
	}
	~DrawPile() {
		delete pile;
	}

	bool estVide() const;

	bool estPleine() const;

	/**
	* Renvoie une carte du paquet
	* renvoie nullptr si rien n'est trouv�
	*/
	Card* piocher();

	void deposer(Card* carte);

	size_t getNbCartes() const {
		return head <= last ? last - head : (taille - head) + last;
	}

	void melanger();

private:
	Card** pile;
	size_t taille;
	int head = 0;
	int last = 0;

	friend class XmlWriter;
	friend ostream& operator<<(ostream& os, const DrawPile drawPile);
};

ostream& operator<<(ostream& os, const DrawPile drawPile);

#endif