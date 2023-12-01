#pragma once

#include "BoardUI.h"
#include "Bag.h"
#include "Board.h"
#include "Action.h"
#include <qlist.h>
#include "DrawPile.h"
#include "Player.h"

class GameHandler {
public:
	static void Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player* player1, Player* player2);
	static void destroy();
	static inline GameHandler& getInstance() { return *GameHandler::instance; }
	bool gameFinished();
	const Player& getWinner();
	void replayTurn();
	void nextAction();
	bool isPlayer1Turn();
	bool suppPlayerGems(Gemmes g);
	bool reservCard(const Card* c, const int position);
	int buyCard(Card* c,const int position);
	Card* asignCard(Card* c);
	bool usePrivilege();
	Card* getDisplayedCard(int rareter, int pos);
	void playerBuyReservCard(int pnum);

	/// <summary>
	/// Affiche la selection de Gemmes en cours
	/// le nombre d�pend de l'action en cours
	/// </summary>
	/// <param name="pos">sa position</param>
	/// <param name="isHover">afficher ou ne pas afficher</param>
	const int gemmesToSelect();

	/// <summary>
	/// On prend les gemmes exitante si leurs positions existe
	/// </summary>
	/// <param name="posTab">tableau de 3 int</param>
	bool gemmesPick(const int* posTab);

	/// <summary>
	/// Remplir le Board Avec le sac
	/// </summary>
	const Board remplirBoard();
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
