#pragma once

#include <vector>
#include "Player.h"
#include "XmlReader.h"
#include "GameHandler.h"

class SingletonNobleHandler {
public:
	// Représente la position d'une carte dans le jeu (sur le plateau, detenu par un joueur)
	enum EnumNoblePosition { Board = 1, Player1 = 2, Player2 = 3 };

	// On supprime la recopie (singleton)
	SingletonNobleHandler(SingletonNobleHandler& copie) = delete;
	// On supprime l'opérateur d'affectation (singleton)
	void operator=(const SingletonNobleHandler&) = delete;

	static SingletonNobleHandler* getInstance();
	static void destroy();

	bool playerCanBuyNoble(const Card& noble, const Player& player) const;
	bool givePlayerNoble(const Card& noble, const Player& player);
	int getNoblePrestigePlayer(const Player& player) const;

	inline const vector<Card*> getNobleCards() const { return noblesCards; }

private:
	// On empêche la construction du singleton
	SingletonNobleHandler() {  }
	~SingletonNobleHandler() {
		for (vector<Card*>::iterator it = noblesCards.begin(); it != noblesCards.end(); it++) {
			delete (*it);
		}
	}

	static SingletonNobleHandler* singleton;

	inline EnumNoblePosition getNoblePositionFromPlayer(const Player& player) const {
		return *SingletonGameHandler::getInstance().player1 == player ? EnumNoblePosition::Player1 : EnumNoblePosition::Player2;
	}
	
	int getNobleIdxFromCard(const Card& noble) const;

	vector<Card*> noblesCards;
	vector<EnumNoblePosition> noblePosition;
};

