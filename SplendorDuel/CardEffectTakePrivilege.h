#pragma once
#include "CardEffect.h"

class CardEffectTakePrivilege : public CardEffect {
public:
	CardEffectTakePrivilege(Card& card, Player& player) : CardEffect(card, player) {}
	void executeEffect() override;
};
