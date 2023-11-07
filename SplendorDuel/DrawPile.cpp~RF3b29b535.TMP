#include "DrawPile.h"

#include <ctime>

bool DrawPile::estVide() const {
	for (int i = 0; i < taille; i++) {
		if (pile[i]) return false;
	}
	return true;
}

Card* DrawPile::piocher() {
	Card* carte = pile[head];
	if (carte) {
		pile[head] = nullptr;
		head = (head + 1) % taille;
	}
	return carte;
}

void DrawPile::deposer(Card* carte) {
	if (carte == nullptr) return;
	pile[last] = carte;
	last = (last + 1) % taille;
}

void DrawPile::melanger() {
	// todo
	/*srand(time(nullptr));
	for (int i = head; i != last; i = (i + 1) % taille) {
		int idx = rand() % ;
		Card* card = pile[i];
		pile[i] = pile[idx];
		pile[idx] = card;
	}*/
}