#ifndef PRIVILEGEHANDLER_H
#define PRIVILEGEHANDLER_H

#include "GameHandler.h"
#include "Player.h"


class SingletonPrivilegeHandler {
public:
	// Represente la position d'un privilege dans le jeu (sur le plateau, detenu par un joueur)
	enum EnumPrivilegePosition { Board = 1, Player1 = 2, Player2 = 3 };

	// On supprime la recopie (singleton)
	SingletonPrivilegeHandler(SingletonPrivilegeHandler& copie) = delete;
	// On supprime l'opérateur d'affectation (singleton)
	void operator=(const SingletonPrivilegeHandler&) = delete;

	static SingletonPrivilegeHandler* getInstance();

	int getPlayerPrivilege(const Player& player);
	void givePlayerPrivilege(const Player& player);
	void putPrivilegeBackOnBoard(const Player& player);
	bool playerHasPrivilege(const Player& player);
private:
	// On empêche la construction du singleton
	SingletonPrivilegeHandler() {}

	inline EnumPrivilegePosition getPrivilegePositionFromPlayer(const Player& player) const {
		return *SingletonGameHandler::getInstance().player1 == player ? EnumPrivilegePosition::Player1 : EnumPrivilegePosition::Player2;
	}

	static SingletonPrivilegeHandler* singleton;

	EnumPrivilegePosition emplacementsPrivilege[3];
};

#endif