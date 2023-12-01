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
	//si il a pas encore fait son action principale
	if (instance->mainActionIsDone == false)
		return;
	//si le joueur doit supprimer une gemmes on bloque toutes les autres actions
	if((isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player1)) || (!isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player2)))
		return;
	if (instance->action.contains(Action::REPLAY)) {
		instance->action.removeAll(Action::REPLAY);
		instance->mainActionIsDone = false;
		return;
	}
	//si il a pas assigné sa carte on bloque
	if (instance->toAsign != nullptr)
		return;
	//si il a pas finit toutes ses actions a faire
	if (instance->action.size() > 0)
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
	//TODO vérifier dans les règles
	if (instance->action.size()==0 && instance->bag.getNbGemmes() != 0) {
		instance->board.remplirBoard(instance->bag);
		return instance->board;
	}
	else {
		return instance->board;
	}
}

const int GameHandler::gemmesToSelect() {
	if (instance->action.size()==0)
		return 3;
	return 1;
}

bool GameHandler::gemmesPick(const int *posTab){
	if (instance->action.size()==0 && instance->mainActionIsDone == true)
		return false;
	Action a = Rules::isPossibleTakeGems(instance->board, posTab, instance->action, instance->typeToPick);
	if (a!=Action::IMPOSSIBLE)
	{
		//Si il n'utilisa pas de privilège et qu'il n'achète pas un perso, 
		// c'est donc la dernière action de son tour
		if (instance->action.size()==0) {
			instance->mainActionIsDone = true;
		}
		else {
			instance->action.removeAll(a);
		}
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
	else if (!isPlayer1Turn() && Rules::playerHaveToSuppGems(instance->player2)) {
		if (instance->player2.removeGem(g, 1)) {
			instance->bag.addGemmes(g);
		}
		else {
			return false;
		}
	}
	//action de voler une gemmes de l'autre joeur
	else if (instance->action.contains(Action::STEAL_GEMMES)){
		//on vole pas l'Or!
		if (g == Gemmes::Or)
			return false;
		if (isPlayer1Turn()) {
			if (instance->player2.removeGem(g, 1)) {
				instance->player1.addGems(g, 1);
				instance->action.removeAll( Action::STEAL_GEMMES);
			}
			else {
				return false;
			}
		}
		else{
			if (instance->player1.removeGem(g, 1)) {
				instance->player2.addGems(g, 1);
				instance->action.removeAll(Action::STEAL_GEMMES);
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
	instance->action.append(Action::RESERV_CARD);
	instance->mainActionIsDone = true;
	instance->displayedCards[c->getLevel()][position] = instance->drawPiles[c->getLevel()]->piocher();
	return true;
}

int GameHandler::buyCard(Card* c, const int position) {
	if (instance->mainActionIsDone)
		return -1;
	if (isPlayer1Turn() && instance->player1.canBuyCard(*c)) {
		//si la carte doit être assigné
		//on vérifie que le jouer pourra l'assigné
		if (c->getEffect().contains(Action::ASIGN_CARD) && Rules::playerCanBuyCardAsign(instance->player1)) {
			instance->toAsign = c;
		}
		instance->player1.buyCard(*c, instance->bag);
	}
	else if(!isPlayer1Turn() && instance->player2.canBuyCard(*c)) {
		//si la carte doit être assigné
		//on vérifie que le jouer pourra l'assigné
		if (c->getEffect().contains(Action::ASIGN_CARD) && Rules::playerCanBuyCardAsign(instance->player2)) {
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
	
	//on ajoute tous les effets de la carte
	for (Action a : c->getEffect()) {
		if (a == Action::PICK_GEMMES) {
			//si le plateau n'a pas les gemmes de ce type on ajoute sinon ça ne sert à rien
			if (instance->board.hasGemOfType(c->getDiscountType())) {
				instance->action.append(a);
				instance->typeToPick = c->getDiscountType();
			}
		}
		else {
			instance->action.append(a);
		}
	}
	// faire l'effet de la carte (rejouer, ajjout de privile, action=STEAL_GEMMES)
	// si replay : instance->replay=true;
	// si c'est un perso on fait juste l'effet sinon :
	//mettre mainActionIsDone a true sauf si il va devoir prendre une gemme (action = PICK_GEMMES)
	//si ce cas la, vérifier que la couleur est présente sur le plateau, sinon pas d'effet
	GameHandler::nextAction();
	//si carte doit etre assigné
	if (instance->action.contains(Action::ASIGN_CARD))
		return 0;
	return 1;
}

Card* GameHandler::asignCard(Card* c) {
	//si la carte n'a pas de type, ou qu'il ne doit pas assigné
	if (instance->toAsign == nullptr || c->getDiscountType() == Gemmes::Vide || !instance->action.contains(Action::ASIGN_CARD))
		return nullptr;
	instance->toAsign->setDiscountType(c->getDiscountType());
	Card* ret = instance->toAsign;
	instance->action.removeAll(Action::ASIGN_CARD);
	instance->toAsign = nullptr;
	GameHandler::nextAction();
	return ret;
}

bool GameHandler::usePrivilege() {
	//vérfier que le joeur peux
	instance->action.append(Action::USE_PRIVILEGE);
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