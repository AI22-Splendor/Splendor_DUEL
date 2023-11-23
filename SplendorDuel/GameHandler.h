#pragma once

#include "BoardUI.h"
#include "Bag.h"
#include "Board.h"
#include "Action.h"
#include "DrawPile.h"

class GameHandler {
public:
	static void Instanciate(Bag& bag, Board& board, DrawPile** drawPiles);
	static void destroy();
	static inline GameHandler& getInstance(){ return *GameHandler::instance; }
	static bool gameFinished();
	static void getWinner();
	static void nextAction();

	/// <summary>
	/// Affiche la selection de Gemmes en cours
	/// le nombre dépend de l'action en cours
	/// </summary>
	/// <param name="pos">sa position</param>
	/// <param name="isHover">afficher ou ne pas afficher</param>
	static const int gemmesToSelect();

	/// <summary>
	/// On prend les gemmes exitante si leurs positions existe
	/// </summary>
	/// <param name="posTab">tableau de 3 int</param>
	static bool gemmesPick(const int *posTab);
private:
	static GameHandler* instance;

	GameHandler(Bag& bag, Board& board, DrawPile** drawPiles) : bag(bag), board(board), drawPiles(drawPiles), action(Action::MAIN_ACTION){};
	GameHandler(const GameHandler&)=delete;
	~GameHandler(){}

	Action action;
	bool player1Joue = true;;
	Bag& bag;
	Board& board;
	DrawPile** drawPiles;
};

