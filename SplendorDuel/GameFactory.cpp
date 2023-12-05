#include "GameFactory.h"

SplendorDuel& GameFactory::buildNewSplendor() {

	Bag* bag = new Bag(25);
	for (int i = 0; i < 4; i++) {
		bag->addGemmes(EnumGemmes::Bleu);
		bag->addGemmes(EnumGemmes::Blanc);
		bag->addGemmes(EnumGemmes::Rouge);
		bag->addGemmes(EnumGemmes::Vert);
		bag->addGemmes(EnumGemmes::Noir);
		if (i < 3) bag->addGemmes(EnumGemmes::Or);
		if (i < 2) bag->addGemmes(EnumGemmes::Perle);
	}

	DrawPile** drawPiles = new DrawPile * [3];
	drawPiles[0] = new DrawPile(0, 30);
	drawPiles[1] = new DrawPile(1, 24);
	drawPiles[2] = new DrawPile(2, 13);

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

	Board* board = new Board;
	board->remplirBoard(*bag);

	SplendorDuel::instanciate(bag, board, drawPiles, player1, player2);
	return SplendorDuel::getInstance();
}