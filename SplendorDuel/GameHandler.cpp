#include "GameHandler.h"
#include "Rules.h"
#include "Player.h"
#include "PrivilegeHandler.h"
#include <math.h>
#include "NobleHandler.h"

GameHandler* GameHandler::instance = nullptr;

GameHandler* GameHandler::Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player* player1, Player* player2) {
	if (GameHandler::instance == nullptr){
		GameHandler::instance = new GameHandler(bag, board, drawPiles, player1, player2);
		GameHandler::instance->player1Joue = (rand () % 2);
		GameHandler::instance->addOtherPlayerPrivilege();
	}
	return GameHandler::instance;
}

Action GameHandler::getLastAction() {
	if (action.size() > 0) {
		return action.at(action.size() - 1);
	}
	else {
		return Action::MAIN_ACTION;
	}
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

<<<<<<< Updated upstream
void GameHandler::nextAction() {
=======
AI* SingletonGameHandler::getAI(){
	if (isPlayer2AI()==true){
		if (AI* ai = dynamic_cast<AI*>(player2)) {
			std::cout << "Successfully casted to AI class." << std::endl;
			return (ai);
		} else {
			std::cout << "Failed to cast to AI class." << std::endl;
		}
		
		}
	}

void SingletonGameHandler::nextAction() {
>>>>>>> Stashed changes
	//si il a pas encore fait son action principale
	if (mainActionIsDone == false)
		return;
	if (action.contains(Action::REPLAY)) {
		action.removeOne(Action::REPLAY);
		mainActionIsDone = false;
		return;
	}
	//si il a pas finit toutes ses actions a faire
	if (action.size() > 0)
		return;
	mainActionIsDone = false;
	Player& currentPlayer = isPlayer1Turn() ? player1 : player2;
	player1Joue = !player1Joue;
}

<<<<<<< Updated upstream
const Board GameHandler::remplirBoard() {
	//TODO vérifier dans les règles
	if (bag.getNbGemmes() != 0) {
		board.remplirBoard(bag);
=======
const Board& SingletonGameHandler::remplirBoard() {
	//TODO vï¿½rifier dans les rï¿½gles
	if (bag->getNbGemmes() != 0) {
		board->remplirBoard(*bag);
>>>>>>> Stashed changes
		addOtherPlayerPrivilege();
	}
	return board;
}

const int GameHandler::gemmesToSelect() {
	if (action.size()==0 || (action.size() == 1 && action.at(0)==Action::REPLAY))
		return 3;
	return 1;
}

bool GameHandler::gemmesPick(const int *posTab){
	Player& current = isPlayer1Turn() ? player1 : player2;
	if (action.size()==0 && mainActionIsDone == true)
		return false;
	if (action.contains(Action::SUPP_GEMS))
		return false;
	Action a = Rules::isPossibleTakeGems(board, posTab, action, typeToPick);
	if (a!=Action::IMPOSSIBLE)
	{
<<<<<<< Updated upstream
		//Si il n'utilisa pas de privilège et qu'il n'achète pas un perso, 
		// c'est donc la dernière action de son tour
		if (action.size() == 0 || (action.size() == 1 && action.contains(Action::REPLAY))) {
=======
		//Si il n'utilisa pas de privilï¿½ge et qu'il n'achï¿½te pas un perso, 
		// c'est donc la derniï¿½re action de son tour
		if (action.size() == 0 || (action.size() == 1 && action.contains(EnumAction::REPLAY))) {
>>>>>>> Stashed changes
			mainActionIsDone = true;
		}
		else {
			action.removeOne(a);
		}
		for (int i = 0; i < 3; i++) {
			if (posTab[i] != -1) {
				//on ajoute la gemme au joueur
				current.addGems(board.prendreGemme(posTab[i]), 1);
			}
		}
		//si le joueur doit supprimer une gemmes on bloque toutes les autres actions
		if (Rules::playerHaveToSuppGems(current))
			action.append(Action::SUPP_GEMS);
		GameHandler::nextAction();
		return true;
	}
	return false;
}

bool GameHandler::isPlayer1Turn() {
	return player1Joue;
}

bool GameHandler::suppPlayerGems(Gemmes g, int p) {
	Player& current = player1Joue ? player1 : player2;
	if (action.contains(Action::SUPP_GEMS)) {
		if (current.removeGem(g, 1)) {
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
		Player other = player1Joue ? player2 : player1;
		if (other.removeGem(g, 1)) {
			current.addGems(g, 1);
			action.removeOne( Action::STEAL_GEMMES);
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	if (Rules::playerHaveToSuppGems(current))
		action.append(Action::SUPP_GEMS);
	else {
		action.removeAll(Action::SUPP_GEMS);
	}
	GameHandler::nextAction();
	return true;
}

bool GameHandler::reservCard(const Card* c, const int position) {
	if (mainActionIsDone || !board.hasGemOfType(Gemmes::Or))
		return false;
	if (action.contains(Action::SUPP_GEMS))
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
	if (action.contains(Action::SUPP_GEMS))
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
	//je gï¿½re pas les actions pour l'instant
	mainActionIsDone = true;
	displayedCards[c->getLevel()][position] = drawPiles[c->getLevel()]->piocher();
	
	//on ajoute tous les effets de la carte
	addAction(c);
<<<<<<< Updated upstream
	GameHandler::nextAction();
	//si carte doit etre assigné
	if (action.contains(Action::ASSIGN_CARD))
=======
	SingletonGameHandler::nextAction();
	//si carte doit etre assignï¿½
	if (action.contains(EnumAction::ASSIGN_CARD))
>>>>>>> Stashed changes
		return 0;
	return 1;
}

<<<<<<< Updated upstream
Card* GameHandler::asignCard(Card* c) {
	//si la carte n'a pas de type, ou qu'il ne doit pas assigné
	if (toAsign == nullptr || c->getDiscountType() == Gemmes::Vide || !action.contains(Action::ASSIGN_CARD))
=======
Card* SingletonGameHandler::assignCard(Card* c) {
	//si la carte n'a pas de type, ou qu'il ne doit pas assignï¿½
	if (toAssign == nullptr || c->getDiscountType() == EnumGemmes::Vide || !action.contains(EnumAction::ASSIGN_CARD))
>>>>>>> Stashed changes
		return nullptr;
	toAsign->setDiscountType(c->getDiscountType());
	Card* ret = toAsign;
	action.removeOne(Action::ASSIGN_CARD);
	toAsign = nullptr;
	GameHandler::nextAction();
	return ret;
}

void GameHandler::addOtherPlayerPrivilege() {
	Player& currentPlayer = player1Joue ? player2 : player1;
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

bool GameHandler::playPrivilege() {
	Player current = player1Joue ? player1 : player2;
	if (PrivilegeHandler::getInstance()->playerHasPrivilege(current)) {
		PrivilegeHandler::getInstance()->putPrivilegeBackOnBoard(current);
		action.append(Action::USE_PRIVILEGE);
		return true;
	}
	return false;
}

void GameHandler::playerBuyReservCard(int pnum) {
	if (pnum == 0) {
		player1.adCarteReserver(-1);
	}
	if (pnum == 1) {
		player2.adCarteReserver(-1);
	}
}

bool GameHandler::buyNoble(const Card* noble) {
	Player currentPlayer = this->player1Joue ? player1 : player2;
	if (Rules::canBuyNoble(*noble, currentPlayer)) {
		NobleHandler::getInstance()->givePlayerNoble(*noble, currentPlayer);
		addAction(noble);
		return true;
	}
	return false;
}

void GameHandler::addAction(const Card* c) {
	Player current = player1Joue ? player1 : player2;
	Player next = player1Joue ? player2 : player1;
	for (Action ac : c->getEffect()) {
		if (ac == ADD_PRIVILEGE) {
			PrivilegeHandler::getInstance()->givePlayerPrivilege(current);
		}else if (ac == STEAL_GEMMES) {
			if (next.getNBGemmes() > 0 && (next.nbOfGems(Gemmes::Or) != next.getNBGemmes())) {
				action.append(ac);
			}
		}
<<<<<<< Updated upstream
		else if (ac == Action::PICK_GEMMES) {
			//si le plateau n'a pas les gemmes de ce type on ajoute sinon ça ne sert à rien
			if (board.hasGemOfType(c->getDiscountType())) {
=======
		else if (ac == EnumAction::PICK_GEMMES) {
			//si le plateau n'a pas les gemmes de ce type on ajoute sinon ï¿½a ne sert ï¿½ rien
			if (board->hasGemOfType(c->getDiscountType())) {
>>>>>>> Stashed changes
				action.append(ac);
				typeToPick = c->getDiscountType();
			}
		}
		else {
			action.append(ac);
		}
	}
}

int GameHandler::getPlayerNbPrivilege(int pnum) {
	if (pnum == 0) {
		return PrivilegeHandler::getInstance()->getPlayerPrivilege(player1);
	}
	else if(pnum == 1) {
		return PrivilegeHandler::getInstance()->getPlayerPrivilege(player2);
	}
}