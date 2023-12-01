#pragma once

#include "BoardUI.h"
#include "Bag.h"
#include "Board.h"
#include "Action.h"
#include <qlist.h>
#include "DrawPile.h"
#include "Player.h"
#include "CardEffect.h"

class GameHandler {
public:
	static void Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player* player1, Player* player2);
	static void destroy();
	static inline GameHandler& getInstance() { return *GameHandler::instance; }
	static bool gameFinished();
	static const Player& getWinner();
	static void replayTurn();
	static void nextAction();
	static bool isPlayer1Turn();
	static bool suppPlayerGems(Gemmes g);
	static bool reservCard(const Card* c, const int position);
	static int buyCard(Card* c,const int position);
	static Card* asignCard(Card* c);
	static bool usePrivilege();
	static Card* getDisplayedCard(int rareter, int pos);
	static void playerBuyReservCard(int pnum);

	/// <summary>
	/// Affiche la selection de Gemmes en cours
	/// le nombre d�pend de l'action en cours
	/// </summary>
	/// <param name="pos">sa position</param>
	/// <param name="isHover">afficher ou ne pas afficher</param>
	static const int gemmesToSelect();

	/// <summary>
	/// On prend les gemmes exitante si leurs positions existe
	/// </summary>
	/// <param name="posTab">tableau de 3 int</param>
	static bool gemmesPick(const int* posTab);

	/// <summary>
	/// Remplir le Board Avec le sac
	/// </summary>
	static const Board remplirBoard();
private:
	static GameHandler* instance;

	GameHandler(Bag& bag, Board& board, DrawPile** drawPiles, Player* player1, Player* player2)
		: bag(bag), typeToPick(Gemmes::Vide), toAsign(nullptr), player1Joue(true), board(board), drawPiles(drawPiles), player1(*player1), mainActionIsDone(false), player2(*player2), action() {
		for (int i = 0; i < 3; i++) {
			displayedCards.push_back(*(new vector<Card*>()));
			for (int j = 0; j < 5 - i; j++) {
				displayedCards[i].push_back(drawPiles[i]->piocher()); 
			}
		}
	}
	GameHandler(const GameHandler&)=delete;
	~GameHandler(){}

	bool mainActionIsDone;
	QList<Action> action;
	bool player1Joue;
	Bag& bag;
	Board& board;
	DrawPile** drawPiles;
	vector<vector<Card*>> displayedCards;
	Player& player1;
	Player& player2;
	Card* toAsign;
	Gemmes typeToPick;
	friend class PrivilegeHandler;
};
