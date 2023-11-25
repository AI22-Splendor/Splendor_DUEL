#pragma once

#include<string>
#include<list>
#include"Card.h"
#include"Gemmes.h"
#include "Bag.h"

using namespace std;

class Player {
public:
	Player(string name);

	string getName() const { return name; }

	unsigned int nbOfGems(Gemmes gem) const { return gems[gem]; }
	const list<const Card*>& getCards() const { return cards; }

	bool canAddGems(const unsigned int nbAdd = 1) const;
	bool addGems(const Gemmes gem, const unsigned int nbAdd = 1);
	bool removeGem(Gemmes gem);
	
	unsigned int getNbCrowns() const;
	unsigned int getPrestige() const;
	unsigned int getDiscount(Gemmes gem) const;
	
	bool canBuyCard(const Card& card) const;
	bool buyCard(const Card& card, Bag& gameBag);

// Protected for future possible AI impl
protected:
	string name;
	list<const Card*> cards;
	unsigned int gems[NB_GEMMES_PAS_VIDE];
};

