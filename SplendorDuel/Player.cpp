#include "Player.h"
#include <list>
#include "NobleHandler.h"

using namespace std;

Player::Player(string name) : name(name), nbCarteReservees(0) {
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		gems[i] = 0;
	}
}

Player::~Player() {
	for (list<const Card*>::iterator it = cards.begin(); it != cards.end(); it++) {
		delete (*it);
	}
}

int Player::canAddGems(const unsigned int nbAdd) const {
	int sum = 0;
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		sum += gems[i];
	}
	return (sum + nbAdd);
}

bool Player::addGems(const EnumGemmes gem, const unsigned int nbAdd) {
	gems[gem] += nbAdd;
	return true;
}

bool Player::removeGem(EnumGemmes gem, const unsigned int nbRemove) {
	if ((gems[gem] < nbRemove) || gem == EnumGemmes::Vide)
		return false;
	gems[gem] -= nbRemove;
	return true;
}

unsigned int Player::getNbCrowns() const {
	unsigned int nbCrowns = 0;
	for (const Card* c: cards) {
		nbCrowns += c->getCrowns();
	}
	return nbCrowns;
}

unsigned int Player::getPrestige(EnumGemmes gem) const {
	unsigned int prestige = 0;
	list<const Card*>::const_iterator it;
	for (it = cards.cbegin(); it != cards.cend(); it++) {
		// An empty Gem as a parameter calculates the total of prestige 
		if (gem == EnumGemmes::Vide || (*it)->getDiscountType() == gem) prestige += (*it)->getPointsPrestige();
	}
	if (gem == EnumGemmes::Vide) prestige += SingletonNobleHandler::getInstance()->getNoblePrestigePlayer(*this);
	return prestige;
}


unsigned int Player::getDiscount(EnumGemmes gem) const {
	unsigned int discount = 0;
	list<const Card*>::const_iterator it;
	for (it = cards.cbegin(); it != cards.cend(); it++) {
		if ((*it)->getDiscountType() == gem) {
			discount += (*it)->getDiscount();
		};
	}
	return discount;
}

bool Player::canBuyCard(const Card& card) const {
	unsigned int* wallet = new unsigned int[NB_GEMMES_PAS_VIDE];
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		wallet[i] = gems[i] + getDiscount(static_cast<EnumGemmes>(i));
	}
	return card.canBeBought(wallet);
}

bool Player::buyCard(const Card& card, Bag& gameBag) {
	if (!canBuyCard(card)) return false;
	
	for (int i = EnumGemmes::Vert; i < NB_GEMMES_PAIEMENTS; i++) {
		EnumGemmes gem = static_cast<EnumGemmes>(i);
		int effectivePrice = card.getPriceForGemme(gem) - getDiscount(gem);
		// If discounts exceed the price 
		if (effectivePrice < 0) effectivePrice = 0;
 		int deltaPrice = effectivePrice - gems[i];
		if (deltaPrice > 0) {
			gems[i] -= effectivePrice - deltaPrice;
			gems[EnumGemmes::Or] -= deltaPrice;
			gameBag.addGemmes(gem, effectivePrice- deltaPrice);
			gameBag.addGemmes(EnumGemmes::Or, deltaPrice);
		}
		else {
			gems[i] -= effectivePrice;
			gameBag.addGemmes(gem, effectivePrice);
		}
	}
	cards.push_back(&card);
	gameBag.melanger();
	return true;
}

unsigned int Player::getNbGemmes() const {
	int sum = 0;
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		sum += gems[i];
	}
	return (sum);
}

unsigned int Player::getHighestGemPrestigeCount() const {
	int max = 0;
	for (int i = 0; i < NB_GEMMES_PAIEMENTS - 1; i++) {
		int prestige = getPrestige(static_cast<EnumGemmes>(i));
		if (prestige > max) max = prestige;
	}
	return max;
}