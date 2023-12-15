#include "GameFactory.h"

SplendorDuel& GameFactory::buildNewSplendor() {

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
<<<<<<< Updated upstream
=======
	if (p1Name.empty())
		p1Name = "Player1";
	if (p2Name.empty())
		p2Name = "Player2";
	Player* player1 = (new Player(p1Name));
	Player* player2;
	AI* ai;

	if(!IA)
		player2 = (new Player(p2Name));
	else {
		//TODO ADD IA
		player2= (new AI());
	}
>>>>>>> Stashed changes

	Player* player1 = (new Player("Player 1"));
	Player* player2 = (new Player("Player 2"));

	Board& board = *(new Board);
	board.remplirBoard(bag);

	SplendorDuel::instanciate(bag, board, drawPiles, player1, player2);
	return SplendorDuel::getInstance();
}