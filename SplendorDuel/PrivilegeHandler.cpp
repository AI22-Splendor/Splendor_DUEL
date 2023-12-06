#include "PrivilegeHandler.h"

SingletonPrivilegeHandler* SingletonPrivilegeHandler::singleton = nullptr;

SingletonPrivilegeHandler* SingletonPrivilegeHandler::getInstance() {
	if (singleton) {
		return singleton;
	}
	
	singleton = new SingletonPrivilegeHandler();
	for (int i = 0; i < 3; i++) {
		singleton->emplacementsPrivilege[i] = EnumPrivilegePosition::Board;
	}

	return singleton;
}

void SingletonPrivilegeHandler::givePlayerPrivilege(const Player& player) {
	EnumPrivilegePosition creditedPlayer = getPrivilegePositionFromPlayer(player);
	EnumPrivilegePosition otherPlayer = creditedPlayer == EnumPrivilegePosition::Player1 ? EnumPrivilegePosition::Player2 : EnumPrivilegePosition::Player1;
	// We check if we can find an unowned privilege
	for (int i = 0; i < 3; i++) {
		if (emplacementsPrivilege[i] == EnumPrivilegePosition::Board) {
			emplacementsPrivilege[i] = creditedPlayer;
			return;
		}
	}
	// If no privilege available, we take one from the other player
	for (int i = 0; i < 3; i++) {
		if (emplacementsPrivilege[i] == otherPlayer) {
			emplacementsPrivilege[i] = creditedPlayer;
			return;
		}
	}
}

void SingletonPrivilegeHandler::putPrivilegeBackOnBoard(const Player& player) {
	EnumPrivilegePosition debitedPlayer = getPrivilegePositionFromPlayer(player);
	for (int i = 0; i < 3; i++) {
		if (emplacementsPrivilege[i] == debitedPlayer) {
			emplacementsPrivilege[i] = EnumPrivilegePosition::Board;
			return;
		}
	}
}

bool SingletonPrivilegeHandler::playerHasPrivilege(const Player& player) {
	EnumPrivilegePosition playerPos = getPrivilegePositionFromPlayer(player);
	for (int i = 0; i < 3; i++) {
		if (emplacementsPrivilege[i] == playerPos) {
			return true;
		}
	}
	return false;
}

int SingletonPrivilegeHandler::getPlayerPrivilege(const Player& player) {
	EnumPrivilegePosition playerPos = getPrivilegePositionFromPlayer(player);
	int nb = 0;
	for (int i = 0; i < 3; i++) {
		if (emplacementsPrivilege[i] == playerPos) {
			nb++;
		}
	}
	return nb;
}