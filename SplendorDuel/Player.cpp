#include "Player.h"
#include <list>

using namespace std;

Player::Player(string name) : name(name) {
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		gems[i] = 0;
		cout <<"gems =" << gems[i] << "\n";
	}
}

int Player::canAddGems(const unsigned int nbAdd) const {
	int sum = 0;
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		sum += gems[i];
	}
	return (sum + nbAdd);
}

bool Player::addGems(const Gemmes gem, const unsigned int nbAdd) {
	gems[gem] += nbAdd;
	cout <<getName() <<" :" << this->getNBGemmes() << "\n";
	return true;
}

bool Player::removeGem(Gemmes gem, const unsigned int nbRemove) {
	if ((gems[gem] < nbRemove) || gem == Gemmes::Vide)
		return false;
	gems[gem] -= nbRemove;
	cout << getName() << " :" << this->getNBGemmes() << "\n";
	return true;
}

unsigned int Player::getNbCrowns() const {
	unsigned int nbCrowns = 0;
	list<const Card*>::const_iterator it;
	for (it = cards.cbegin(); it != cards.cend(); it++) {
		nbCrowns += (*it)->getCrowns();
	}
	return nbCrowns;
}

unsigned int Player::getPrestige(Gemmes gem) const {
	unsigned int prestige = 0;
	list<const Card*>::const_iterator it;
	for (it = cards.cbegin(); it != cards.cend(); it++) {
		// Since an empty Gem represents all the types of discount at once
		// we can use it to calculate the total amount of prestige and type specific prestige 
		if (gem == Gemmes::Vide || (*it)->getDiscountType() == gem) prestige += (*it)->getPointsPrestige();
	}
	return prestige;
}


unsigned int Player::getDiscount(Gemmes gem) const {
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
		wallet[i] = gems[i] + getDiscount(static_cast<Gemmes>(i));
	}
	return card.canBeBought(wallet);
}

bool Player::buyCard(const Card& card, Bag& gameBag) {
	if (!canBuyCard(card)) return false;
	
	for (int i = Gemmes::Vert; i < NB_GEMMES_PAIEMENTS; i++) {
		Gemmes gem = static_cast<Gemmes>(i);
		int effectivePrice = card.getPriceForGemme(gem) - getDiscount(gem);
 		int deltaPrice = effectivePrice - gems[i];
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
	cards.push_back(&card);
	gameBag.melanger();
	return true;
}

unsigned int Player::getNBGemmes()const {
	int sum = 0;
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		sum += gems[i];
	}
	return (sum);
}