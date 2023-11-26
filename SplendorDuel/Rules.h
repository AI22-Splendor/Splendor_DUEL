#pragma once
#include "Board.h"
#include "Action.h"
#include "Player.h"

class Rules
{
public:
	static Action isPossibleTakeGems(const Board b, const int* posTab, Action action);
	static bool playerWon(const Player& player);
private:
};

