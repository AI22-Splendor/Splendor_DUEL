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
		cout << board << "\n";

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
private:
	// IS A TEST, REMOVE
	static void testBoard(Board& board, Bag& bag) {
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
	}

	static void testDrawPile(DrawPile& drawPile) {
		cout << drawPile << endl;

		drawPile.melanger();

		cout << "=Melange======================" << endl;
		cout << drawPile << endl;

		Card* c1 = drawPile.piocher();
		Card* c2 = drawPile.piocher();
		Card* c3 = drawPile.piocher();
		cout << "=3 cartes piochees============" << endl;
		cout << *c1 << " - " << *c2 << " - " << *c3 << endl;
		cout << drawPile << endl;

		cout << "=2 cartes remises=============" << endl;
		cout << *c1 << endl;
		drawPile.deposer(c2);
		drawPile.deposer(c3);
		cout << drawPile << endl;

		cout << "=Melange======================" << endl;
		drawPile.melanger();
		cout << drawPile << endl;
	}
}; 
