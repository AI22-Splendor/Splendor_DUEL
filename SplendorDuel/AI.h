#pragma once
#include "Player.h"
class AI : public Player
{
public:
	AI() : Player("AI"), isplaying(false) {};
	void play();

private:
	bool isplaying;
	void doAction(QList<EnumAction> a);
};