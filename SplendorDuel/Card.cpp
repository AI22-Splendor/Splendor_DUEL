#include "Card.h"

Card::Card(const unsigned int level, const unsigned int ptsPrestige, const Gemmes bonusType, const unsigned int nbBonus, 
	const unsigned int crowns, const string imageSrc) {
	if (1 > level && level > 3) {
		char* error = new char[35];
		sprintf(error, "%d is not a valid level (1-3)\n", level);
		throw new MyException(error);
	}
	this->level = level;
	this->ptsPrestige = ptsPrestige;
	this->discountType = bonusType;
	this->discount = nbBonus;
	this->crowns = crowns;
	for (int i = 0; i < NB_GEMMES_PAIEMENTS; i++) {
		this->cost[i] = 0;
	}
	this->imageSrc = QString(imageSrc.c_str());
}

void Card::setCost(const Gemmes type, const unsigned int price) {
	if (type == Gemmes::Vide || type == Gemmes::Or) {
		char* error = new char[35];
		sprintf(error, "This type cannot have a	cost (%d)\n", type);
		throw new MyException(error);
	}
	this->cost[type] = price;
}

extern const unsigned int NB_GEMMES_PAIEMENTS;

bool Card::canBeBought(const unsigned int wallet[NB_GEMMES_PAS_VIDE]) const {
	int nbGold = wallet[Gemmes::Or];
	for (int i = 0; i < NB_GEMMES_PAIEMENTS; i++) {
		if (wallet[i] + nbGold < cost[i]) {
			return false;
		}
		int delta = cost[i] - wallet[i];
		if (delta > 0) nbGold -= delta;
	}
	return true;
}

ostream& operator<<(ostream& os, const Card card) {
	return os << "Card[" << card.level << "/" << card.ptsPrestige << "P/" << card.discountType << "x" << card.discount << "/" << card.crowns << "C]";
}