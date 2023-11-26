#include "GameHandler.h"
#include "Rules.h"
#include "Player.h"

GameHandler* GameHandler::instance = nullptr;

void GameHandler::Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player* player1, Player* player2) {
	if(GameHandler::instance == nullptr)
		GameHandler::instance = new GameHandler(bag, board, drawPiles, player1, player2);
}

void GameHandler::destroy() {
	delete GameHandler::instance;
	GameHandler::instance = nullptr;
}

bool GameHandler::gameFinished() {
	return Rules::playerWon(instance->player1) || Rules::playerWon(instance->player2);
}

const Player& GameHandler::getWinner() {
	if (gameFinished()) {
		return Rules::playerWon(instance->player1) ? instance->player1 : instance->player2;
	}
	throw new MyException("No player won yet");
}

void GameHandler::replayTurn() {
	return;
}

void GameHandler::nextAction() {
	//on change de joueur
	if (instance->action != Action::SUPP_GEMS && instance->action != Action::PICK_GEMMES) {
		instance->player1Joue = !instance->player1Joue;
		cout << "next p";
	}
}

const Board GameHandler::remplirBoard() {
	if (instance->action == Action::MAIN_ACTION && instance->bag.getNbGemmes() != 0) {
		instance->board.remplirBoard(instance->bag);
		return instance->board;
	}
	else {
		return instance->board;
	}
}

const int GameHandler::gemmesToSelect() {
	if (instance->action == Action::MAIN_ACTION)
		return 3;
	return 1;
}

bool GameHandler::gemmesPick(const int *posTab){
	switch (Rules::isPossibleTakeGems(instance->board, posTab, instance->action))
	{
	case Action::ADD_PRIVILEGE:
		//TODO LE PRIVILEGE

	case (Action::MAIN_ACTION || Action::ADD_PRIVILEGE):
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				//on ajoute la gemme au joueur
				if (isPlayer1Turn()) {
					instance->player1.addGems(instance->board.prendreGemme(posTab[i]), 1);
					if (instance->player1.getNBGemmes()>10) {
						instance->action = Action::SUPP_GEMS;
					}
				}
				else {
					instance->player2.addGems(instance->board.prendreGemme(posTab[i]), 1);
					if (instance->player2.getNBGemmes() > 10) {
						instance->action = Action::SUPP_GEMS;
					}
				}
			}
		}
		GameHandler::nextAction();
		return true;

	case Action::IMPOSSIBLE:
		return false;
	}
}

bool GameHandler::isPlayer1Turn() {
	//return true;
	return !instance->player1Joue;
}

bool GameHandler::suppPlayerGems(Gemmes g) {
	if (instance->action != Action::SUPP_GEMS)
		return false;
	if (isPlayer1Turn()) {
		if (instance->player1.removeGem(g, 1)) {
			instance->bag.addGemmes(g);
			if (instance->player1.getNBGemmes() <= 10) {
				instance->action = Action::MAIN_ACTION;
				instance->nextAction();
				return true;
			}
		}
		else {
			return false;
		}
	}
	else {
		if (instance->player2.removeGem(g, 1)) {
			instance->bag.addGemmes(g);
			if (instance->player2.getNBGemmes() <= 10) {
				instance->action = Action::MAIN_ACTION;
				instance->nextAction();
				return true;
			}
		}
		else {
			return false;
		}
	}
}