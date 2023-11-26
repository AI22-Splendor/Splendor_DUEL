#pragma once
#include "CardEffect.h"

class CardEffectPlayAgain : public CardEffect {
public:
	CardEffectPlayAgain(Card& card, Player& player) : CardEffect(card, player) {}
	void executeEffect() override;
};

