#pragma once

#include <vector>
#include "Player.h"
#include "XmlReader.h"
#include "GameHandler.h"

class NobleHandler {
public:
	enum NoblePosition { Board = 1, Player1 = 2, Player2 = 3 };
	// On supprime la recopie (singleton)
	NobleHandler(NobleHandler& copie) = delete;
	// On supprime l'opérateur d'affectation (singleton)
	void operator=(const NobleHandler&) = delete;

	static NobleHandler* getInstance();

	bool playerCanBuyNoble(const Card& noble, const Player& player) const;
	bool givePlayerNoble(const Card& noble, const Player& player);
	int getNoblePrestigePlayer(const Player& player) const;

	inline const vector<Card*> getNobleCards() const { return noblesCards; }

private:
	// On empêche la construction du singleton
	NobleHandler() {  }

	static NobleHandler* singleton;

	inline NoblePosition getNoblePositionFromPlayer(const Player& player) const {
		return GameHandler::getInstance().player1 == player ? NoblePosition::Player1 : NoblePosition::Player2;
	}
	
	int getNobleIdxFromCard(const Card& noble) const;

	vector<Card*> noblesCards;
	vector<NoblePosition> noblePosition;
};

