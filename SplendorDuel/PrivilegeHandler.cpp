#include "PrivilegeHandler.h"
#include "GameHandler.h"

PrivilegeHandler* PrivilegeHandler::singleton = nullptr;

PrivilegeHandler* PrivilegeHandler::getInstance() {
	if (singleton) {
		return singleton;
	}
	
	singleton = new PrivilegeHandler();
	for (int i = 0; i < 3; i++) {
		singleton->emplacementsPrivilege[i] = PrivilegePosition::Board;
	}

	return singleton;
}

void PrivilegeHandler::givePlayerPrivilege(const Player& player) {
	PrivilegePosition creditedPlayer = GameHandler::getInstance().player1 == player ? PrivilegePosition::Player1 : PrivilegePosition::Player2;
	PrivilegePosition otherPlayer = creditedPlayer == PrivilegePosition::Player1 ? PrivilegePosition::Player2 : PrivilegePosition::Player1;
	// We check if we can find an unowned privilege
	for (int i = 0; i < 3; i++) {
		if (singleton->emplacementsPrivilege[i] == PrivilegePosition::Board) {
			singleton->emplacementsPrivilege[i] = creditedPlayer;
			return;
		}
	}
	// If no privilege available, we take one from the other player
	for (int i = 0; i < 3; i++) {
		if (singleton->emplacementsPrivilege[i] == otherPlayer) {
			singleton->emplacementsPrivilege[i] = creditedPlayer;
			return;
		}
	}
}

void PrivilegeHandler::putPrivilegeBackOnBoard(const Player& player) {
	PrivilegePosition debitedPlayer = GameHandler::getInstance().player1 == player ? PrivilegePosition::Player1 : PrivilegePosition::Player2;
	for (int i = 0; i < 3; i++) {
		if (singleton->emplacementsPrivilege[i] == debitedPlayer) {
			singleton->emplacementsPrivilege[i] = PrivilegePosition::Board;
			return;
		}
	}
}