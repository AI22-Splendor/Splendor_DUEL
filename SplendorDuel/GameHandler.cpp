#include "GameHandler.h"
#include "Rules.h"
#include "Player.h"

GameHandler* GameHandler::instance = nullptr;

void GameHandler::Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player& player1, Player& player2) {
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
	return;
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
	case Action::IMPOSSIBLE:
		return false;

	case Action::MAIN_ACTION:
		for (int i = 0; i < 3; i++) {
		 	instance->bag.addGemmes(instance->board.prendreGemme(posTab[i]));
		}
		return true;
	case Action::ADD_PRIVILEGE:
		//TODO
		if (instance->action == Action::MAIN_ACTION) {
			for (int i = 0; i < 3; i++) {
				instance->bag.addGemmes(instance->board.prendreGemme(posTab[i]));
			}
		}
		//TODO LE PRIVILEGE
		return true;
	}
}

bool GameHandler::isPlayer1Turn() {
	return !instance->player1Joue;
}