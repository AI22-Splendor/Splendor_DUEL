#include "Player.h"
#include <list>

using namespace std;

Player::Player(string name) : name(name) {
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		gems[i] = 0;
	}
}

bool Player::canAddGem() const {
	int sum = 0;
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		sum += gems[i];
	}
	return sum < 10;
}

bool Player::addGem(Gemmes gem) {
	if (canAddGem()) {
		gems[gem]++;
		return true;
	}
	return false;
}

bool Player::removeGem(Gemmes gem) {
	if (gems[gem] <= 0 || gem == Gemmes::Vide) return false;
	gems[gem]--;
	return true;
}

unsigned int Player::getNbCrowns() const {
	unsigned int nbCrowns = 0;
	list<Card*>::const_iterator it;
	for (it = cards.cbegin(); it != cards.cend(); it++) {
		nbCrowns += (*it)->getCrowns();
	}
	return nbCrowns;
}
unsigned int Player::getDiscount(Gemmes gem) const {
	unsigned int discount = 0;
	list<Card*>::const_iterator it;
	for (it = cards.cbegin(); it != cards.cend(); it++) {
		if ((*it)->getDiscountType() == gem) {
			discount += (*it)->getDiscount();
		};
	}
	return discount;
}

bool Player::canBuyCard(const Card& card) const {
	return card.canBeBought(gems);
}

bool Player::buyCard(const Card& card, Bag& gameBag) {
	if (!canBuyCard(card)) return false;
	
	for (int i = Gemmes::Vert; i < NB_GEMMES_PAIEMENTS; i++) {
		Gemmes gem= static_cast<Gemmes>(i);
		int deltaPrice = card.getPriceForGemme(gem) - gems[i];
		if (deltaPrice > 0) {
			gems[i] -= card.getPriceForGemme(gem) - deltaPrice;
			gems[Gemmes::Or] -= deltaPrice;
			gameBag.addGemmes(gem, card.getPriceForGemme(gem) - deltaPrice);
			gameBag.addGemmes(Gemmes::Or, deltaPrice);
		}
		else {
			gems[i] -= card.getPriceForGemme(gem);
			gameBag.addGemmes(gem, card.getPriceForGemme(gem));
		}
	}
	gameBag.melanger();
	return true;
}