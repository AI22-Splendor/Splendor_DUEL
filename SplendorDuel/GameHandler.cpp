#include "GameHandler.h"
GameHandler* GameHandler::instance = nullptr;

void GameHandler::Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, BoardUI* boardui) {
	if(GameHandler::instance == nullptr)
		GameHandler::instance = new GameHandler(bag, board, drawPiles, boardui);
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

void GameHandler::gemmesHover(const int pos, bool isHover) {
	//on ne selectionne pas les gemmes vide et les Gemmes or si c'est l'action principale
	if (instance->board.connaitreGemmes(pos) != Gemmes::Vide) {
		if (instance->action == Action::MAIN_ACTION) {
			instance->boardUI->hover(pos, true, isHover);
		}
		else {
			instance->boardUI->hover(pos, false, isHover);
		}
	}
}

void GameHandler::gemmesPick(){
	//TODO les règles de vérifications que l'on peut
	if (instance->action == Action::MAIN_ACTION) {
		bool possible = true;
		for (int i = 0; i < 3; i++) {
			if (instance->boardUI->getSelectedGemmes(i)==-1 || instance->board.connaitreGemmes(instance->boardUI->getSelectedGemmes(i))==Gemmes::Vide)
				possible = false;
		}
		if (possible) {
			for (int i = 0; i < 3; i++) {
				//on les remets dans le bag
				instance->bag.addGemmes(instance->board.prendreGemme(instance->boardUI->getSelectedGemmes(i)));
			}
			instance->boardUI->setGemmes(instance->board);
		}
	}
	else {
		if (instance->boardUI->getSelectedGemmes(0) != -1) {
			instance->bag.addGemmes(instance->board.prendreGemme(instance->boardUI->getSelectedGemmes(0)));
			instance->boardUI->setGemmes(instance->board);
		}
	}
}