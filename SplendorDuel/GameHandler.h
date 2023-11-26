#pragma once

#include "BoardUI.h"
#include "Bag.h"
#include "Board.h"
#include "Action.h"
#include "DrawPile.h"
#include "Player.h"
#include "CardEffect.h"

class GameHandler {
public:
	static void Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, Player& player1, Player& player2);
	static void destroy();
	static inline GameHandler& getInstance() { return *GameHandler::instance; }
	static bool gameFinished();
	static const Player& getWinner();
	static void replayTurn();
	static void nextAction();
	static bool isPlayer1Turn();

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

	GameHandler(Bag& bag, Board& board, DrawPile** drawPiles, Player& player1, Player& player2)
		: bag(bag), board(board), drawPiles(drawPiles), player1(player1), player2(player2), action(Action::MAIN_ACTION) {}
	GameHandler(const GameHandler&) = delete;
	~GameHandler() {}

	Action action;
	bool player1Joue = true;
	Bag& bag;
	Board& board;
	DrawPile** drawPiles;
	Player& player1;
	Player& player2;
	friend class PrivilegeHandler;
};
