#include "GameHandler.h"
#include "Rules.h"
#include "Player.h"
#include "PrivilegeHandler.h"
#include <math.h>

GameHandler* GameHandler::instance = nullptr;

GameHandler* GameHandler::Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player* player1, Player* player2) {
	if (GameHandler::instance == nullptr){
		GameHandler::instance = new GameHandler(bag, board, drawPiles, player1, player2);
		GameHandler::instance->player1Joue = (rand () % 2);
		PrivilegeHandler::getInstance()->givePlayerPrivilege(GameHandler::instance->player1Joue ? GameHandler::instance->player2 : GameHandler::instance->player1);
	}
	return GameHandler::instance;
}

void GameHandler::destroy() {
	delete GameHandler::instance;
	GameHandler::instance = nullptr;
}

bool GameHandler::gameFinished() {
	return Rules::playerWon(player1) || Rules::playerWon(player2);
}

const Player& GameHandler::getWinner() {
	if (gameFinished()) {
		return Rules::playerWon(player1) ? player1 : player2;
	}
	throw new MyException("No player won yet");
}

void GameHandler::replayTurn() {
	return;
}

void GameHandler::nextAction() {
	//si il a pas encore fait son action principale
	if (mainActionIsDone == false)
		return;
	//si le joueur doit supprimer une gemmes on bloque toutes les autres actions
	if((isPlayer1Turn() && Rules::playerHaveToSuppGems(player1)) || (!isPlayer1Turn() && Rules::playerHaveToSuppGems(player2)))
		return;
	if (action.contains(Action::REPLAY)) {
		action.removeOne(Action::REPLAY);
		mainActionIsDone = false;
		return;
	}
	//si il a pas assigné sa carte on bloque
	if (toAsign != nullptr)
		return;
	//si il a pas finit toutes ses actions a faire
	if (action.size() > 0)
		return;
	mainActionIsDone = false;
	Player& currentPlayer = isPlayer1Turn() ? player1 : player2;
	
	/*
	list<Action> possibleOptionalActions;
	if (PrivilegeHandler::playerHasPrivilege(currentPlayer)) possibleOptionalActions.push_back(Action::USE_PRIVILEGE);
	if (bag.getNbGemmes() > 0) possibleOptionalActions.push_back(Action::FILL_BOARD);

	list<Action> possibleMandatoryActions;
	possibleMandatoryActions.push_back(Action::PICK_GEMMES);
	if (board.hasGemOfType(Gemmes::Or)) possibleMandatoryActions.push_back(Action::RESERV_CARD);
	bool canBuyCard = false;
	for (int i = 0; i < 3; i++) {
		vector<Card*>::const_iterator it = displayedCards[i].cbegin();
		for (; it != displayedCards[i].cend(); it++) {
			if ((*it)!=nullptr && currentPlayer.canBuyCard(*(*it))) {
				canBuyCard = true;
				possibleMandatoryActions.push_back(Action::BUY_CARD);
				break;
			}
		}
		if (canBuyCard) break;
	}*/
	player1Joue = !player1Joue;
}

const Board GameHandler::remplirBoard() {
	//TODO vérifier dans les règles
	if (bag.getNbGemmes() != 0) {
		board.remplirBoard(bag);
		this->addCurrentPlayerPrivilege();
	}
	return board;
}

const int GameHandler::gemmesToSelect() {
	if (action.size()==0 || (action.size() == 1 && action.at(0)==Action::REPLAY))
		return 3;
	return 1;
}

bool GameHandler::gemmesPick(const int *posTab){
	if (action.size()==0 && mainActionIsDone == true)
		return false;
	Action a = Rules::isPossibleTakeGems(board, posTab, action, typeToPick);
	if (a!=Action::IMPOSSIBLE)
	{
		//Si il n'utilisa pas de privilège et qu'il n'achète pas un perso, 
		// c'est donc la dernière action de son tour
		if (action.size() == 0 || (action.size() == 1 && action.contains(Action::REPLAY))) {
			mainActionIsDone = true;
		}
		else {
			action.removeOne(a);
		}
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				//on ajoute la gemme au joueur
				if (isPlayer1Turn()) {
					player1.addGems(board.prendreGemme(posTab[i]), 1);
				}
				else {
					player2.addGems(board.prendreGemme(posTab[i]), 1);
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
	return player1Joue;
}

bool GameHandler::suppPlayerGems(Gemmes g, int p) {
	if (isPlayer1Turn() && Rules::playerHaveToSuppGems(player1)) {
		if (player1.removeGem(g, 1)) {
			bag.addGemmes(g);
		}
		else {
			return false;
		}
	}
	else if (!isPlayer1Turn() && Rules::playerHaveToSuppGems(player2)) {
		if (player2.removeGem(g, 1)) {
			bag.addGemmes(g);
		}
		else {
			return false;
		}
	}
	//action de voler une gemmes de l'autre joeur
	else if (action.contains(Action::STEAL_GEMMES)){
		if ((isPlayer1Turn() && p == 1) || (!isPlayer1Turn() && p == 2))
			return false;
		//on vole pas l'Or!
		if (g == Gemmes::Or)
			return false;
		if (isPlayer1Turn()) {
			if (player2.removeGem(g, 1)) {
				player1.addGems(g, 1);
				action.removeOne( Action::STEAL_GEMMES);
			}
			else {
				return false;
			}
		}
		else{
			if (player1.removeGem(g, 1)) {
				player2.addGems(g, 1);
				action.removeOne(Action::STEAL_GEMMES);
			}
			else {
				return false;
			}
		}
	}
	GameHandler::nextAction();
	return true;
}

bool GameHandler::reservCard(const Card* c, const int position) {
	if (mainActionIsDone || !board.hasGemOfType(Gemmes::Or))
		return false;
	//si il peux reserver
	if (isPlayer1Turn() && player1.getNbCarteReserver()<3) {
		player1.adCarteReserver(1);
	}
	else if (!isPlayer1Turn() && player2.getNbCarteReserver() < 3) {
		player2.adCarteReserver(1);
	}
	else {
		return false;
	}
	action.append(Action::RESERV_CARD);
	mainActionIsDone = true;
	displayedCards[c->getLevel()][position] = drawPiles[c->getLevel()]->piocher();
	return true;
}

int GameHandler::buyCard(Card* c, const int position) {
	if (mainActionIsDone)
		return -1;
	Player& p = player1Joue ? player1 : player2;
	if (c->getEffect().contains(Action::ASSIGN_CARD) && !Rules::playerCanBuyCardAsign(p)) {
		return -1;
	}
	if (p.canBuyCard(*c)) {
		if(c->getEffect().contains(Action::ASSIGN_CARD)){
			toAsign = c;
		}
		p.buyCard(*c, bag);
	}
	else {
		return -1;
	}
	//je gère pas les actions pour l'instant
	mainActionIsDone = true;
	displayedCards[c->getLevel()][position] = drawPiles[c->getLevel()]->piocher();
	
	//on ajoute tous les effets de la carte
	addAction(c);
	GameHandler::nextAction();
	//si carte doit etre assigné
	if (action.contains(Action::ASSIGN_CARD))
		return 0;
	return 1;
}

Card* GameHandler::asignCard(Card* c) {
	//si la carte n'a pas de type, ou qu'il ne doit pas assigné
	if (toAsign == nullptr || c->getDiscountType() == Gemmes::Vide || !action.contains(Action::ASSIGN_CARD))
		return nullptr;
	toAsign->setDiscountType(c->getDiscountType());
	Card* ret = toAsign;
	action.removeOne(Action::ASSIGN_CARD);
	toAsign = nullptr;
	GameHandler::nextAction();
	return ret;
}

void GameHandler::addCurrentPlayerPrivilege(){
	Player& currentPlayer = player1Joue ? player1 : player2;
	PrivilegeHandler::getInstance()->givePlayerPrivilege(currentPlayer);
}

bool GameHandler::usePrivilege() {
	Player& currentPlayer = player1Joue ? player1 : player2;
	if (!PrivilegeHandler::getInstance()->playerHasPrivilege(currentPlayer)) {
		return false;
	}
	action.append(Action::USE_PRIVILEGE);
	PrivilegeHandler::getInstance()->putPrivilegeBackOnBoard(currentPlayer);
	return true;
}

Card* GameHandler::getDisplayedCard(int rareter, int pos) {
	if (rareter < 3 && rareter >= 0) {
		if (rareter == 0 && pos < 5 && pos >= 0)
			return displayedCards[rareter][pos];
		if (rareter == 1 && pos < 4 && pos >= 0)
			return displayedCards[rareter][pos];
		if (rareter == 2 && pos < 3 && pos >= 0)
			return displayedCards[rareter][pos];
	}
	return nullptr;
}

void GameHandler::playerBuyReservCard(int pnum) {
	if (pnum == 0) {
		player1.adCarteReserver(-1);
	}
	if (pnum == 1) {
		player2.adCarteReserver(-1);
	}
}

bool GameHandler::buyNoble(const Card* c) {
	Player current = this->player1Joue ? player1 : player2;
	if (Rules::canBuyNoble(current)) {
		addAction(c);
		return true;
	}
	return false;
}

void GameHandler::addAction(const Card* c) {
	Player current = player1Joue ? player1 : player2;
	Player next = player1Joue ? player2 : player1;
	for (Action ac : c->getEffect()) {
		if (ac == ADD_PRIVILEGE) {
			addCurrentPlayerPrivilege();
		}else if (ac == STEAL_GEMMES) {
			if (next.getNBGemmes() > 0 && (next.nbOfGems(Gemmes::Or) != next.getNBGemmes())) {
				action.append(ac);
			}
		}
		else if (ac == Action::PICK_GEMMES) {
			//si le plateau n'a pas les gemmes de ce type on ajoute sinon ça ne sert à rien
			if (board.hasGemOfType(c->getDiscountType())) {
				action.append(ac);
				typeToPick = c->getDiscountType();
			}
		}
		else {
			action.append(ac);
		}
	}
}