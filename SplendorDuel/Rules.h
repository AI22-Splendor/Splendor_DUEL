#pragma once
#include "Board.h"
#include "Action.h"
class Rules
{
public:
	static Action isPossibleTakeGems(const Board b, const int* posTab, Action action);
private:
};

