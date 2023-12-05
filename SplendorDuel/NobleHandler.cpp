#include "NobleHandler.h"

SingletonNobleHandler* SingletonNobleHandler::singleton = nullptr;

SingletonNobleHandler* SingletonNobleHandler::getInstance() {
	if (singleton) {
		return singleton;
	}

	singleton = new SingletonNobleHandler();

	singleton->noblesCards = XmlReader::getNoblesFromXml();
	for (int i = 0; i < singleton->noblesCards.size(); i++) {
		singleton->noblePosition.push_back(Board);
	}

	return singleton;
}

void SingletonNobleHandler::destroy() {
	delete singleton;
}

bool SingletonNobleHandler::playerCanBuyNoble(const Card& noble, const Player& player) const {
	int nobleIdx = getNobleIdxFromCard(noble);
	cout << nobleIdx << endl;
	// Card is not a noble
	if (nobleIdx < 0) return false;
	// If noble is not on board, cannot buy it 
	if (noblePosition[nobleIdx] != EnumNoblePosition::Board) return false;

	EnumNoblePosition newPosition = getNoblePositionFromPlayer(player);

	int cpt = 0;
	for (EnumNoblePosition pos : noblePosition) {
		if (pos == newPosition) cpt++;
	}
	// Player already has 2 nobles
	if (cpt >= 2) return false;
	// Player needs to have at least 6 crowns if he wants a second noble
	if (cpt == 1 && player.getNbCrowns() < 6) return false;
	// Player needs to have at least 3 crowns if he wants his first noble
	if (cpt == 0 && player.getNbCrowns() < 3) return false;
	
	return true;
}

bool SingletonNobleHandler::givePlayerNoble(const Card& noble, const Player& player) {
	if (!this->playerCanBuyNoble(noble, player)) return false;

	EnumNoblePosition newPosition = this->getNoblePositionFromPlayer(player);
	noblePosition[this->getNobleIdxFromCard(noble)] = newPosition;

	cout << noblePosition[this->getNobleIdxFromCard(noble)];

	return true;
}

int SingletonNobleHandler::getNoblePrestigePlayer(const Player& player) const {
	int pts = 0;
	EnumNoblePosition playerPos = getNoblePositionFromPlayer(player);

	for (int i = 0; i < noblePosition.size(); i++) {
		if (noblePosition[i] == playerPos) pts += noblesCards[i]->getPointsPrestige();
	}
	return pts;
}

int SingletonNobleHandler::getNobleIdxFromCard(const Card& noble) const {
	int nobleIdx = -1;
	for (int i = 0; i < noblesCards.size(); i++) {
		if (noble == *noblesCards[i]) {
			nobleIdx = i;
			break;
		}
	}
	return nobleIdx;
}