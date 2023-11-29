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
		vector<DrawPile*> drawPiles;
		drawPiles.push_back(new DrawPile(0, 30));
		drawPiles.push_back(new DrawPile(1, 24));
		drawPiles.push_back(new DrawPile(2, 13));

		list<Card*> cards = XmlReader::getCardsFromXml();
		list<Card*>::iterator it;
		for (it = cards.begin(); it != cards.end(); it++) {
			drawPiles[(*it)->getLevel()]->deposer(*it);
		}
		for (int i = 0; i < 3; i++) {
			drawPiles[i]->melanger();
		}

		Player* player1 = (new Player("Player 1"));
		Player* player2 = (new Player("Player 2"));

		Board& board = *(new Board);
		board.remplirBoard(bag);

		SplendorDuel::instanciate(bag, board, drawPiles, player1, player2);
		return SplendorDuel::getInstance(); 
	}
};