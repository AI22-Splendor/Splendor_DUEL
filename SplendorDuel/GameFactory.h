#pragma once

#include "SplendorDuel.h"
#include "Board.h"
#include "Bag.h"
#include "DrawPile.h"
#include <iostream>
#include "Player.h"
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


		// TODO : une vraie analyse de comment générer les cartes
		DrawPile** drawPiles;
		drawPiles = new DrawPile * [3];
		for (int i = 0; i < 3; i++) {
			drawPiles[i] = new DrawPile(i, 30 - (i * 5));
			for (int j = 0; j < (30 - (i * 5)); j++) {
				drawPiles[i]->deposer(new Card(i, i + j, Gemmes::Rouge, j, j % 5 == 0 ? j : 0));
			}
			drawPiles[i]->melanger();
		}

		Player& player1 = *(new Player("Player 1"));
		Player& player2 = *(new Player("Player 2"));

		bag.suppGemmes(Gemmes::Or);
		bag.suppGemmes(Gemmes::Rouge, 3);
		bag.suppGemmes(Gemmes::Vert, 2);

		player1.addGems(Gemmes::Or, 1);
		player1.addGems(Gemmes::Rouge, 3);
		player1.addGems(Gemmes::Vert, 2);

		Card testCard = *(new Card(3, 10, Gemmes::Vert, 1, 2));
		testCard.setCost(Gemmes::Rouge, 3);
		testCard.setCost(Gemmes::Vert, 2);
		cout << player1.canBuyCard(testCard) << endl;

		testCard.setCost(Gemmes::Vert, 3);
		cout << player1.canBuyCard(testCard) << endl;

		testCard.setCost(Gemmes::Rouge, 4);
		cout << player1.canBuyCard(testCard) << endl;

		testCard.setCost(Gemmes::Rouge, 3);
		cout << player1.buyCard(testCard, bag);

		cout << testCard << endl;

		cout << "Prestige : " << player1.getPrestige()
			<< " Crowns : " << player1.getNbCrowns()
			<< "\n Green discount : " << player1.getDiscount(Gemmes::Vert);

		Board& board = *(new Board);
		board.remplirBoard(bag);

		SplendorDuel::instanciate(bag, board, drawPiles, player1, player2);
		return SplendorDuel::getInstance(); 
	}
};