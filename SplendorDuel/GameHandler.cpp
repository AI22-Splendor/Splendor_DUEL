#include "GameHandler.h"
#include "Rules.h"
GameHandler* GameHandler::instance = nullptr;

void GameHandler::Instanciate(Bag& bag, Board& board, DrawPile** drawPiles) {
	if(GameHandler::instance == nullptr)
		GameHandler::instance = new GameHandler(bag, board, drawPiles);
}

void GameHandler::destroy() {
	delete GameHandler::instance;
	GameHandler::instance = nullptr;
}

bool GameHandler::gameFinished() {
	return true;
}

void GameHandler::getWinner() {
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

int GameHandler::getPlayerTurn() {
	return 1;
}