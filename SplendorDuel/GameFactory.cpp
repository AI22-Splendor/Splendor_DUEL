#include "GameFactory.h"

SplendorDuel& GameFactory::buildNewSplendor(const bool IA, string p1Name, string p2Name) {
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
<<<<<<< HEAD
<<<<<<< Updated upstream
=======
=======
>>>>>>> 837c85eb72fd14b5c5985edc33ba1f6b11654a39
	if (p1Name.empty())
		p1Name = "Player1";
	if (p2Name.empty())
		p2Name = "Player2";
	Player* player1 = (new Player(p1Name));
	Player* player2;
<<<<<<< HEAD
	AI* ai;

=======
>>>>>>> 837c85eb72fd14b5c5985edc33ba1f6b11654a39
	if(!IA)
		player2 = (new Player(p2Name));
	else {
		//TODO ADD IA
<<<<<<< HEAD
		player2= (new AI());
	}
>>>>>>> Stashed changes
=======
		player2 = (new Player("IA"));
	}
>>>>>>> 837c85eb72fd14b5c5985edc33ba1f6b11654a39

	Board* board = new Board;
	board->remplirBoard(*bag);

	SplendorDuel::instanciate(bag, board, drawPiles, player1, player2);
	return SplendorDuel::getInstance();
}