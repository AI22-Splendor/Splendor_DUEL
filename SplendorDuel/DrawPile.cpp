#include "DrawPile.h"

#include <ctime>
#include <iostream>
using namespace std;

bool DrawPile::estVide() const {
	for (int i = 0; i < taille; i++) {
		if (pile[i]) return false;
	}
	return true;
}

bool DrawPile::estPleine() const {
	for (int i = 0; i < taille; i++) {
		if (!pile[i]) return false;
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
	srand(time(nullptr));
	if (estPleine()) {
		for (int i = 0; i < taille; i++) {
			int idx = rand() % taille;
			Card* temp = pile[i];
			pile[i] = pile[idx];
			pile[idx] = temp;
		}
	}
	else if (head < last) {
		for (int i = head; i < last; i++) {
			int idx = (rand() % (last - head)) + head;
			Card* temp = pile[i];
			pile[i] = pile[idx];
			pile[idx] = temp;
		}
	}
	else if (head > last) {
		for (int i = head; i < taille; i++) {
			int idx = ((rand() % (taille - head)) + head + (rand() % last)) % taille;
			Card* temp = pile[i];
			pile[i] = pile[idx];
			pile[idx] = temp;
		}
		for (int i = 0; i < last; i++) {
			int idx = ((rand() % (taille - head)) + head + (rand() % last)) % taille;
			Card* temp = pile[i];
			pile[i] = pile[idx];
			pile[idx] = temp;
		}
	}
}

ostream& operator<<(ostream& os, const DrawPile drawPile) {
	os << "[ ";
	if (drawPile.estPleine()) {
		for (int i = 0; i < drawPile.taille; i++) {
			os << *(drawPile.pile[i]);
			if (i != drawPile.taille - 1) os << ", ";
		}
	}
	else if(!drawPile.estVide()) {
		for (int i = drawPile.head; i != drawPile.last; i = (i + 1) % drawPile.taille) {
			if (drawPile.pile[i]) os << *(drawPile.pile[i]);
			if (i != (drawPile.last - 1) % drawPile.taille) os << ", ";
		}
	}
	return os << " ]";
}