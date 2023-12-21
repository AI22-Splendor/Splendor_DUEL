#pragma once
#include "Player.h"
class AI : public Player
{
public:
	AI() : Player("AI"), isplaying(false) {};
	void play();
	~AI() {for (const Card* c : cards) {delete c;}}

private:
	bool isplaying;
	void doAction(QList<EnumAction> a);
};