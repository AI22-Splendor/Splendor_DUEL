#include "NobleHandler.h"

NobleHandler* NobleHandler::singleton = nullptr;

NobleHandler* NobleHandler::getInstance() {
	if (singleton) {
		return singleton;
	}

	singleton = new NobleHandler();

	singleton->noblesCards = XmlReader::getNoblesFromXml();
	for (int i = 0; i < singleton->noblesCards.size(); i++) {
		singleton->noblePosition.push_back(Board);
	}

	return singleton;
}

bool NobleHandler::playerCanBuyNoble(const Card& noble, const Player& player) const {
	int nobleIdx = getNobleIdxFromCard(noble);
	cout << nobleIdx << endl;
	// Card is not a noble
	if (nobleIdx < 0) return false;
	// If noble is not on board, cannot buy it 
	if (noblePosition[nobleIdx] != NoblePosition::Board) return false;

	NoblePosition newPosition = GameHandler::getInstance().player1 == player ? NoblePosition::Player1 : NoblePosition::Player2;

	int cpt = 0;
	for (NoblePosition pos : noblePosition) {
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

bool NobleHandler::givePlayerNoble(const Card& noble, const Player& player) {
	if (!this->playerCanBuyNoble(noble, player)) return false;

	NoblePosition newPosition = this->getNoblePositionFromPlayer(player);
	noblePosition[this->getNobleIdxFromCard(noble)] = newPosition;

	cout << noblePosition[this->getNobleIdxFromCard(noble)];

	return true;
}

int NobleHandler::getNoblePrestigePlayer(const Player& player) const {
	int pts = 0;
	NoblePosition playerPos = getNoblePositionFromPlayer(player);

	for (int i = 0; i < noblePosition.size(); i++) {
		if (noblePosition[i] == playerPos) pts += noblesCards[i]->getPointsPrestige();
	}
	return pts;
}

int NobleHandler::getNobleIdxFromCard(const Card& noble) const {
	int nobleIdx = -1;
	for (int i = 0; i < noblesCards.size(); i++) {
		if (noble == *noblesCards[i]) {
			nobleIdx = i;
			break;
		}
	}
	return nobleIdx;
}