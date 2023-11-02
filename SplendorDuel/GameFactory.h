#pragma once

#include "SplendorDuel.h"
#include "Board.h"
#include "Bag.h"
#include <iostream>

using namespace std;

class GameFactory {
public:
	static SplendorDuel& buildSplendor() {
		Bag bag(25);
		Board board;

		for (int i = 0; i < 4; i++) {
			bag.addGemmes(Gemmes::Bleu);
			bag.addGemmes(Gemmes::Blanc);
			bag.addGemmes(Gemmes::Rouge);
			bag.addGemmes(Gemmes::Vert);
			bag.addGemmes(Gemmes::Noir);
			if (i < 3) bag.addGemmes(Gemmes::Or);
			if (i < 2) bag.addGemmes(Gemmes::Perle);
		}

		board.remplirBoard(bag);
		cout << endl << "======================" << endl;
		cout << board;

		Gemmes gem1 = board.prendreGemme(12);
		Gemmes gem2 = board.prendreGemme(0);
		board.prendreGemme(1);
		cout << endl << "=" << gem1 << "=" << gem2 << "===============" << endl;
		cout << board;

		bag.addGemmes(gem1);
		bag.addGemmes(gem2);
		board.remplirBoard(bag);
		cout << endl << "======================" << endl;
		cout << board;

		return *(new SplendorDuel(bag, board));
	}
};
