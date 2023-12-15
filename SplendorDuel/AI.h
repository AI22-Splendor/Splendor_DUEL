#pragma once

#include<string>
#include<list>
#include"Card.h"
#include"Gemmes.h"
#include "Bag.h"
#include "Player.h"
#include "CardUI.h"
#include "GameHandler.h"
#include "CompleteBoardUI.h"
#include "BoardUI.h"

using namespace std;

class AI : public Player {
    public:
        AI() :Player("IA") {}
        void play();
};

