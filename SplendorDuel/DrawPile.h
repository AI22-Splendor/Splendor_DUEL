#pragma once

#include "Card.h"

#include<iostream>
using namespace std;

class DrawPile {
public:
	DrawPile(const unsigned int level, size_t taille): level(level), taille(taille) {
		pile = new Card*[taille];
		for (int i = 0; i < taille; i++) pile[i] = nullptr;
	}

	bool estVide() const;

	bool estPleine() const;

	/**
	* Renvoie une carte du paquet
	* renvoie nullptr si rien n'est trouvé
	*/
	Card* piocher();

	void deposer(Card* carte);

	size_t getNbCartes() const {
		return head <= last ? last - head : (taille - head) + last;
	}

	void melanger();

private:
	unsigned int level;
	Card** pile;
	size_t taille;
	int head = 0;
	int last = 0;
	friend ostream& operator<<(ostream& os, const DrawPile drawPile);
};

ostream& operator<<(ostream& os, const DrawPile drawPile);

