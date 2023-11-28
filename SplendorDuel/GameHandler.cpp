#include "GameHandler.h"
#include "Rules.h"
#include "Player.h"
#include "PrivilegeHandler.h"

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
	//si le joueur doit supprimer une gemmes on bloque toutes les autres actions
	if (instance->mainActionIsDone == false)
		return;
	if((isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player1)) || (!isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player2)))
		return;
	instance->mainActionIsDone = false;
	Player& currentPlayer = isPlayer1Turn() ? instance->player1 : instance->player2;
	
	list<Action> possibleOptionalActions;
	if (PrivilegeHandler::playerHasPrivilege(currentPlayer)) possibleOptionalActions.push_back(Action::USE_PRIVILEGE);
	if (instance->bag.getNbGemmes() > 0) possibleOptionalActions.push_back(Action::FILL_BOARD);

	list<Action> possibleMandatoryActions;
	possibleMandatoryActions.push_back(Action::PICK_GEMMES);
	if (instance->board.hasGemOfType(Gemmes::Or)) possibleMandatoryActions.push_back(Action::RESERV_CARD);
	bool canBuyCard = false;
	for (int i = 0; i < 3; i++) {
		vector<Card*>::const_iterator it = instance->displayedCards[i].cbegin();
		for (; it != instance->displayedCards[i].cend(); it++) {
			if (currentPlayer.canBuyCard(*(*it))) {
				canBuyCard = true;
				possibleMandatoryActions.push_back(Action::BUY_CARD);
				break;
			}
		}
		if (canBuyCard) break;
	}
	instance->player1Joue = !instance->player1Joue;
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
	if (Rules::isPossibleTakeGems(instance->board, posTab) && instance->mainActionIsDone==false)
	{
		instance->mainActionIsDone = true;
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				//on ajoute la gemme au joueur
				if (isPlayer1Turn()) {
					instance->player1.addGems(instance->board.prendreGemme(posTab[i]), 1);
				}
				else {
					instance->player2.addGems(instance->board.prendreGemme(posTab[i]), 1);
				}
			}
		}
		GameHandler::nextAction();
		return true;
	}
	else {
		return false;
	}
}

bool GameHandler::isPlayer1Turn() {
	return instance->player1Joue;
}

bool GameHandler::suppPlayerGems(Gemmes g) {
	if (isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player1)) {
		if (instance->player1.removeGem(g, 1)) {
			instance->bag.addGemmes(g);
		}
		else {
			return false;
		}
	}
	else if (!isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player2)){
		if (instance->player2.removeGem(g, 1)) {
			instance->bag.addGemmes(g);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	GameHandler::nextAction();
	return true;
}