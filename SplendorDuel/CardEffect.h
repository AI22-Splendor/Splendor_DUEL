#pragma once
#include "Card.h"
#include "Player.h"

class CardEffect {
public:
	CardEffect(Card& card, Player& player): card(card), player(player) {}
	virtual ~CardEffect() {}
	virtual void executeEffect() = 0;
protected:
	Card& card;
	Player& player;
};

