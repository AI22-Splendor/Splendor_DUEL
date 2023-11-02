#pragma once

#include "Card.h"

class DrawPile {
public:
	DrawPile(const unsigned int level, size_t taille): level(level), taille(taille) {
		pile = new Card*[taille];
		for (int i = 0; i < taille; i++) pile[i] = nullptr;
	}

	bool estVide() const;

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
	unsigned int head = 0;
	unsigned int last = 0;
};

