#pragma once
#include "Player.h"


class PrivilegeHandler {
public:
	enum PrivilegePosition { Board = 1, Player1 = 2, Player2 = 3 };
	// On supprime la recopie (singleton)
	PrivilegeHandler(PrivilegeHandler& copie) = delete;
	// On supprime l'op�rateur d'affectation (singleton)
	void operator=(const PrivilegeHandler&) = delete;

	static PrivilegeHandler* getInstance();

	static void givePlayerPrivilege(const Player& player);
	static void putPrivilegeBackOnBoard(const Player& player);
	static bool playerHasPrivilege(const Player& player);
private:
	// On emp�che la construction du singleton
	PrivilegeHandler() {}

	static PrivilegeHandler* singleton;

	PrivilegePosition emplacementsPrivilege[3];
};

