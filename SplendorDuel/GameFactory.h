#pragma once

#include "SplendorDuel.h"
#include "Board.h"
#include "Bag.h"
#include "DrawPile.h"
#include <iostream>
#include "Player.h"
#include "XmlReader.h"

using namespace std;

class GameFactory {
public:
	static SplendorDuel& buildNewSplendor();
};