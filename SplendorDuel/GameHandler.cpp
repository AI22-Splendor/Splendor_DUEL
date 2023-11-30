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
	if (instance->action != Action::MAIN_ACTION)
		return;
	//si il a pas encore fait son action principale
	if (instance->mainActionIsDone == false)
		return;
	//si le joueur doit supprimer une gemmes on bloque toutes les autres actions
	if((isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player1)) || (!isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player2)))
		return;
	if (instance->replay) {
		instance->replay = false;
		instance->mainActionIsDone = false;
		return;
	}
	//si il a pas assigné sa carte on bloque
	if (instance->toAsign != nullptr)
		return;
	instance->mainActionIsDone = false;
	Player& currentPlayer = isPlayer1Turn() ? instance->player1 : instance->player2;
	
	/*
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
			if ((*it)!=nullptr && currentPlayer.canBuyCard(*(*it))) {
				canBuyCard = true;
				possibleMandatoryActions.push_back(Action::BUY_CARD);
				break;
			}
		}
		if (canBuyCard) break;
	}*/
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
	if (instance->action == Action::MAIN_ACTION && instance->mainActionIsDone == true)
		return false;
	if (Rules::isPossibleTakeGems(instance->board, posTab, instance->action))
	{
		//Si il n'utilisa pas de privilège et qu'il n'achète pas un perso, 
		// c'est donc la dernière action de son tour
		if (instance->action != Action::USE_PRIVILEGE) {
			instance->mainActionIsDone = true;
		}
		instance->action = Action::MAIN_ACTION;
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
	if (instance->action == Action::MAIN_ACTION) {
		if (isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player1)) {
			if (instance->player1.removeGem(g, 1)) {
				instance->bag.addGemmes(g);
			}
			else {
				return false;
			}
		}
		else if (!isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player2)) {
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
	}
	//action de voler une gemmes de l'autre joeur
	else if (instance->action == Action::STEAL_GEMMES) {
		//on vole pas l'Or!
		if (g == Gemmes::Or)
			return false;
		if (isPlayer1Turn()) {
			if (instance->player2.removeGem(g, 1)) {
				instance->bag.addGemmes(g);
				instance->player1.addGems(g, 1);
				instance->action = Action::MAIN_ACTION;
			}
		}
		else{
			if (instance->player1.removeGem(g, 1)) {
				instance->bag.addGemmes(g);
				instance->player2.addGems(g, 1);
				instance->action = Action::MAIN_ACTION;
			}
		}
	}
	GameHandler::nextAction();
	return true;
}

bool GameHandler::reservCard(const Card* c, const int position) {
	if (instance->mainActionIsDone || !instance->board.hasGemOfType(Gemmes::Or))
		return false;
	//si il peux reserver
	if (isPlayer1Turn() && instance->player1.getNbCarteReserver()<3) {
		instance->player1.adCarteReserver(1);
	}
	else if (!isPlayer1Turn() && instance->player2.getNbCarteReserver() < 3) {
		instance->player1.adCarteReserver(1);
	}
	else {
		return -1;
	}
	instance->action = Action::RESERV_CARD;
	instance->mainActionIsDone = true;
	instance->displayedCards[c->getLevel()][position] = instance->drawPiles[c->getLevel()]->piocher();
	//TODO
	// ne pas oublié de vérif que le jouer n'a pas déjà 3 cartes réserver et qu'il y a 
	// au moins 1 or sur le plateau
	//MEtre l'action sur RESERV_CARD 
	// et ne pas modifier mainActionIsDone, c'est prendre l'or qui terminera l'action principale
	return true;
}

int GameHandler::buyCard(Card* c, const int position) {
	if (instance->mainActionIsDone)
		return -1;
	if (isPlayer1Turn() && instance->player1.canBuyCard(*c)) {
		//si la carte doit être assigné
		//on vérifie que le jouer pourra l'assigné
		if (c->getDiscountType() == Gemmes::Vide && Rules::playerCanBuyCardAsign(instance->player1)) {
			instance->toAsign = c;
		}
		instance->player1.buyCard(*c, instance->bag);
	}
	else if(!isPlayer1Turn() && instance->player2.canBuyCard(*c)) {
		//si la carte doit être assigné
		//on vérifie que le jouer pourra l'assigné
		if (c->getDiscountType() == Gemmes::Vide && Rules::playerCanBuyCardAsign(instance->player2)) {
			instance->toAsign = c;
		}
		instance->player2.buyCard(*c, instance->bag);
	}
	else {
		return -1;
	}
	//je gère pas les actions pour l'instant
	instance->mainActionIsDone = true;
	instance->displayedCards[c->getLevel()][position] = instance->drawPiles[c->getLevel()]->piocher();

	//si la carte doit être assigné, la retenir et retourner 0
	// faire l'effet de la carte (rejouer, ajjout de privile, action=STEAL_GEMMES)
	// si replay : instance->replay=true;
	// si c'est un perso on fait juste l'effet sinon :
	//mettre mainActionIsDone a true sauf si il va devoir prendre une gemme (action = PICK_GEMMES)
	//si ce cas la, vérifier que la couleur est présente sur le plateau, sinon pas d'effet
	GameHandler::nextAction();
	//si carte doit etre assigné
	if (c->getDiscountType() == Gemmes::Vide)
		return 0;
	return 1;
}

Card* GameHandler::asignCard(Card* c) {
	if (instance->toAsign == nullptr || c->getDiscountType() == Gemmes::Vide)
		return nullptr;
	instance->toAsign->setDiscountType(c->getDiscountType());
	Card* ret = instance->toAsign;
	instance->toAsign = nullptr;
	GameHandler::nextAction();
	return ret;
}

bool GameHandler::usePrivilege() {
	//vérfier que le joeur peux
	//mettre l'ation sur use_PRIVILEGE
	return true;
}

Card* GameHandler::getDisplayedCard(int rareter, int pos) {
	if (rareter < 3 && rareter >= 0) {
		if (rareter == 0 && pos < 5 && pos >= 0)
			return instance->displayedCards[rareter][pos];
		if (rareter == 1 && pos < 4 && pos >= 0)
			return instance->displayedCards[rareter][pos];
		if (rareter == 2 && pos < 3 && pos >= 0)
			return instance->displayedCards[rareter][pos];
	}
	return nullptr;
}

void GameHandler::playerBuyReservCard(int pnum) {
	if (pnum == 0) {
		instance->player1.adCarteReserver(-1);
	}
	if (pnum == 1) {
		instance->player2.adCarteReserver(-1);
	}
}