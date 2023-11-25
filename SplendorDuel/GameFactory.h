#pragma once

#include "SplendorDuel.h"
#include "Board.h"
#include "Bag.h"
#include "DrawPile.h"
#include <iostream>
using namespace std;

class GameFactory {
public:
	static SplendorDuel& buildNewSplendor() {

		Bag& bag = *(new Bag(25));
		for (int i = 0; i < 4; i++) {
			bag.addGemmes(Gemmes::Bleu);
			bag.addGemmes(Gemmes::Blanc);
			bag.addGemmes(Gemmes::Rouge);
			bag.addGemmes(Gemmes::Vert);
			bag.addGemmes(Gemmes::Noir);
			if (i < 3) bag.addGemmes(Gemmes::Or);
			if (i < 2) bag.addGemmes(Gemmes::Perle);
		}
		
		Board& board = *(new Board);
		board.remplirBoard(bag);

		// TODO : une vraie analyse de comment générer les cartes
		DrawPile** drawPiles;
		drawPiles = new DrawPile*[3];
		for (int i = 0; i < 3; i++) {
			drawPiles[i] = new DrawPile(i, 30 - (i * 5));
			for (int j = 0; j < (30 - (i * 5)); j++) {
				drawPiles[i]->deposer(new Card(i, i + j, Gemmes::Rouge, j, j%5 == 0 ? j : 0));
			}
			drawPiles[i]->melanger();
		}


		return *(new SplendorDuel(bag, board, drawPiles));
	}
}; 
