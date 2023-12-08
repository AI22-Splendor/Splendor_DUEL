#include "GameHandler.h"
#include "Rules.h"
#include "Player.h"
#include "PrivilegeHandler.h"
#include <math.h>
#include "NobleHandler.h"

SingletonGameHandler* SingletonGameHandler::instance = nullptr;

SingletonGameHandler* SingletonGameHandler::Instanciate(Bag* bag, Board* board, DrawPile** drawPiles, Player* player1, Player* player2) {
	if (SingletonGameHandler::instance == nullptr){
		SingletonGameHandler::instance = new SingletonGameHandler(bag, board, drawPiles, player1, player2);
		SingletonGameHandler::instance->player1Joue = (rand () % 2);
		SingletonGameHandler::instance->addOtherPlayerPrivilege();
	}
	return SingletonGameHandler::instance;
}

EnumAction SingletonGameHandler::getLastAction() {
	if (action.size() > 0) {
		return action.at(action.size() - 1);
	}
	else {
		return EnumAction::MAIN_ACTION;
	}
}

void SingletonGameHandler::destroy() {
	delete SingletonGameHandler::instance;
	SingletonGameHandler::instance = nullptr;
}

bool SingletonGameHandler::gameFinished() {
	return Rules::playerWon(*player1) || Rules::playerWon(*player2);
}

const Player& SingletonGameHandler::getWinner() {
	if (gameFinished()) {
		return Rules::playerWon(*player1) ? *player1 : *player2;
	}
	throw new MyException("No player won yet");
}

void SingletonGameHandler::nextAction() {
	//si il a pas encore fait son action principale
	if (mainActionIsDone == false)
		return;
	if (action.contains(EnumAction::REPLAY)) {
		action.removeOne(EnumAction::REPLAY);
		mainActionIsDone = false;
		return;
	}
	//si il a pas finit toutes ses actions a faire
	if (action.size() > 0)
		return;
	mainActionIsDone = false;
	// Player& currentPlayer = isPlayer1Turn() ? player1 : player2;
	player1Joue = !player1Joue;
}

const Board& SingletonGameHandler::remplirBoard() {
	//TODO vérifier dans les règles
	if (bag->getNbGemmes() != 0) {
		board->remplirBoard(*bag);
		addOtherPlayerPrivilege();
	}
	return *board;
}

const int SingletonGameHandler::gemmesToSelect() {
	if (action.size()==0 || (action.size() == 1 && action.at(0)==EnumAction::REPLAY))
		return 3;
	return 1;
}

bool SingletonGameHandler::gemmesPick(const int *posTab){
	Player& current = isPlayer1Turn() ? *player1 : *player2;
	if (action.size()==0 && mainActionIsDone == true)
		return false;
	if (action.contains(EnumAction::SUPP_GEMS))
		return false;
	EnumAction a = Rules::isPossibleTakeGems(*board, posTab, action, typeToPick);
	if (a!=EnumAction::IMPOSSIBLE)
	{
		//Si il n'utilisa pas de privilège et qu'il n'achète pas un perso, 
		// c'est donc la dernière action de son tour
		if (action.size() == 0 || (action.size() == 1 && action.contains(EnumAction::REPLAY))) {
			mainActionIsDone = true;
		}
		else {
			action.removeOne(a);
		}
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				//on ajoute la gemme au joueur
				current.addGems(board->prendreGemme(posTab[i]), 1);
			}
		}
		//si le joueur doit supprimer une gemmes on bloque toutes les autres actions
		if (Rules::playerHaveToSuppGems(current))
			action.append(EnumAction::SUPP_GEMS);
		SingletonGameHandler::nextAction();
		return true;
	}
	return false;
}

bool SingletonGameHandler::isPlayer1Turn() {
	return player1Joue;
}

bool SingletonGameHandler::suppPlayerGems(EnumGemmes g, int p) {
	Player& current = player1Joue ? *player1 : *player2;
	if (action.contains(EnumAction::SUPP_GEMS)) {
		if (current.removeGem(g, 1)) {
			bag->addGemmes(g);
		}
		else {
			return false;
		}
	}
	//action de voler une gemmes de l'autre joeur
	else if (action.contains(EnumAction::STEAL_GEMMES)){
		if ((isPlayer1Turn() && p == 1) || (!isPlayer1Turn() && p == 2))
			return false;
		//on vole pas l'Or!
		if (g == EnumGemmes::Or)
			return false;
		Player& other = player1Joue ? *player2 : *player1;
		if (other.removeGem(g, 1)) {
			current.addGems(g, 1);
			action.removeOne( EnumAction::STEAL_GEMMES);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	if (Rules::playerHaveToSuppGems(current))
		action.append(EnumAction::SUPP_GEMS);
	else {
		action.removeAll(EnumAction::SUPP_GEMS);
	}
	SingletonGameHandler::nextAction();
	return true;
}

bool SingletonGameHandler::reservCard(const Card* c, const int position) {
	if (mainActionIsDone || !board->hasGemOfType(EnumGemmes::Or))
		return false;
	if (action.contains(EnumAction::SUPP_GEMS))
		return false;
	//si il peux reserver
	if (isPlayer1Turn() && player1->getNbCarteReserver()<3) {
		player1->adCarteReserver(1);
	}
	else if (!isPlayer1Turn() && player2->getNbCarteReserver() < 3) {
		player2->adCarteReserver(1);
	}
	else {
		return false;
	}
	action.append(EnumAction::RESERV_CARD);
	mainActionIsDone = true;
	displayedCards[c->getLevel()][position] = drawPiles[c->getLevel()]->piocher();
	return true;
}

int SingletonGameHandler::buyCard(Card* c, const int position) {
	if (mainActionIsDone)
		return -1;
	if (action.contains(EnumAction::SUPP_GEMS))
		return -1;
	Player& p = player1Joue ? *player1 : *player2;
	if (c->getEffect().contains(EnumAction::ASSIGN_CARD) && !Rules::playerCanBuyCardAsign(p)) {
		return -1;
	}
	if (p.canBuyCard(*c)) {
		if(c->getEffect().contains(EnumAction::ASSIGN_CARD)){
			toAssign = c;
		}
		p.buyCard(*c, *bag);
	}
	else {
		return -1;
	}
	//je gère pas les actions pour l'instant
	mainActionIsDone = true;
	displayedCards[c->getLevel()][position] = drawPiles[c->getLevel()]->piocher();
	
	//on ajoute tous les effets de la carte
	addAction(c);
	SingletonGameHandler::nextAction();
	//si carte doit etre assigné
	if (action.contains(EnumAction::ASSIGN_CARD))
		return 0;
	return 1;
}

Card* SingletonGameHandler::assignCard(Card* c) {
	//si la carte n'a pas de type, ou qu'il ne doit pas assigné
	if (toAssign == nullptr || c->getDiscountType() == EnumGemmes::Vide || !action.contains(EnumAction::ASSIGN_CARD))
		return nullptr;
	toAssign->setDiscountType(c->getDiscountType());
	Card* ret = toAssign;
	action.removeOne(EnumAction::ASSIGN_CARD);
	toAssign = nullptr;
	SingletonGameHandler::nextAction();
	return ret;
}

void SingletonGameHandler::addOtherPlayerPrivilege() {
	Player& currentPlayer = player1Joue ? *player2 : *player1;
	SingletonPrivilegeHandler::getInstance()->givePlayerPrivilege(currentPlayer);
}

bool SingletonGameHandler::usePrivilege() {
	Player& currentPlayer = player1Joue ? *player1 : *player2;
	if (!SingletonPrivilegeHandler::getInstance()->playerHasPrivilege(currentPlayer)) {
		return false;
	}
	action.append(EnumAction::USE_PRIVILEGE);
	SingletonPrivilegeHandler::getInstance()->putPrivilegeBackOnBoard(currentPlayer);
	return true;
}

Card* SingletonGameHandler::getDisplayedCard(int rarete, int pos) {
	if (rarete < 3 && rarete >= 0) {
		if (rarete == 0 && pos < 5 && pos >= 0)
			return displayedCards[rarete][pos];
		if (rarete == 1 && pos < 4 && pos >= 0)
			return displayedCards[rarete][pos];
		if (rarete == 2 && pos < 3 && pos >= 0)
			return displayedCards[rarete][pos];
	}
	return nullptr;
}

bool SingletonGameHandler::playPrivilege() {
	Player& current = player1Joue ? *player1 : *player2;
	if (SingletonPrivilegeHandler::getInstance()->playerHasPrivilege(current)) {
		SingletonPrivilegeHandler::getInstance()->putPrivilegeBackOnBoard(current);
		action.append(EnumAction::USE_PRIVILEGE);
		return true;
	}
	return false;
}

void SingletonGameHandler::playerBuyReservCard(int pnum) {
	if (pnum == 0) {
		player1->adCarteReserver(-1);
	}
	if (pnum == 1) {
		player2->adCarteReserver(-1);
	}
}

bool SingletonGameHandler::buyNoble(const Card* noble) {
	Player& currentPlayer = player1Joue ? *player1 : *player2;
	if (Rules::canBuyNoble(*noble, currentPlayer)) {
		SingletonNobleHandler::getInstance()->givePlayerNoble(*noble, currentPlayer);
		addAction(noble);
		return true;
	}
	return false;
}

void SingletonGameHandler::addAction(const Card* c) {
	Player& current = player1Joue ? *player1 : *player2;
	Player& next = player1Joue ? *player2 : *player1;
	for (EnumAction ac : c->getEffect()) {
		if (ac == ADD_PRIVILEGE) {
			SingletonPrivilegeHandler::getInstance()->givePlayerPrivilege(current);
		}else if (ac == STEAL_GEMMES) {
			if (next.getNBGemmes() > 0 && (next.nbOfGems(EnumGemmes::Or) != next.getNBGemmes())) {
				action.append(ac);
			}
		}
		else if (ac == EnumAction::PICK_GEMMES) {
			//si le plateau n'a pas les gemmes de ce type on ajoute sinon ça ne sert à rien
			if (board->hasGemOfType(c->getDiscountType())) {
				action.append(ac);
				typeToPick = c->getDiscountType();
			}
		}
		else {
			action.append(ac);
		}
	}
}

int SingletonGameHandler::getPlayerNbPrivilege(int pnum) {
	if (pnum == 0) {
		return SingletonPrivilegeHandler::getInstance()->getPlayerPrivilege(*player1);
	}
	else if(pnum == 1) {
		return SingletonPrivilegeHandler::getInstance()->getPlayerPrivilege(*player2);
	}
}

Message SingletonGameHandler::getActionMessage()const {
	if (action.size() > 0) {
		return XmlReader::getActionMessage(action.at(action.size() - 1));
	}
	else {
		return Message("", "#ffffff");
	}
}