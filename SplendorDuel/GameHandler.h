#pragma once

#include "Bag.h"
#include "Board.h"
#include "DrawPile.h"

class GameHandler {
public:
	GameHandler(Bag& bag, Board& board, DrawPile** drawPiles) : bag(bag), board(board), drawPiles(drawPiles) {}

	bool gameFinished();

	void getWinner();

	void nextAction();

	~GameHandler();
private:
	bool player1Joue = true;
	Bag& bag;
	Board& board;
	DrawPile** drawPiles;
};

