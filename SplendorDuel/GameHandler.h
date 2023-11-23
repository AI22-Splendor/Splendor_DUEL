#pragma once

#include "BoardUI.h"
#include "Bag.h"
#include "Board.h"
#include "DrawPile.h"

class GameHandler {
public:
	static void Instanciate(Bag& bag, Board& board, DrawPile** drawPiles, BoardUI *boardUI);
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
	static void gemmesHover(const int pos, bool isHover);

	static void gemmesPick();
private:
	enum Action {
		MAIN_ACTION = 1,
		PICK_GEMMES = 2,
	};

	static GameHandler* instance;

	GameHandler(Bag& bag, Board& board, DrawPile** drawPiles, BoardUI* boardUI) : bag(bag), board(board), drawPiles(drawPiles), action(Action::MAIN_ACTION), boardUI(boardUI) {};
	GameHandler(const GameHandler&)=delete;
	~GameHandler(){}

	BoardUI* boardUI;
	Action action;
	bool player1Joue = true;;
	Bag& bag;
	Board& board;
	DrawPile** drawPiles;
};

