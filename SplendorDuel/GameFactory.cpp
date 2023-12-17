#include "GameFactory.h"

SplendorDuel& GameFactory::buildNewSplendor(const bool IA, string p1Name, string p2Name) {
	string filename = "./res/savefile.xml";
	
	// Check if savefile exists
	struct stat buffer;
	if (stat(filename.c_str(), &buffer) == 0) {
		return buildNewSplendorFromSavefile(filename);
	}
	else {
		return buildNewSplendorFromScratch(IA, p1Name, p2Name);
	}
}

SplendorDuel& GameFactory::buildNewSplendorFromScratch(const bool IA, string p1Name, string p2Name) {
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
	drawPiles[0] = new DrawPile(30);
	drawPiles[1] = new DrawPile(24);
	drawPiles[2] = new DrawPile(13);

	list<Card*> cards = XmlReader::getCardsFromXml();
	list<Card*>::iterator it;
	for (it = cards.begin(); it != cards.end(); it++) {
		drawPiles[(*it)->getLevel()]->deposer(*it);
	}
	for (int i = 0; i < 3; i++) {
		drawPiles[i]->melanger();
	}

	Player* player1 = (new Player(p1Name));
	Player* player2;
	if (!IA)
		player2 = (new Player(p2Name));
	else {
		player2 = (new Player("IA"));
	}

	Board* board = new Board;
	board->remplirBoard(*bag);

	SplendorDuel::instanciate(bag, board, drawPiles, player1, player2);
	return SplendorDuel::getInstance();
}


SplendorDuel& GameFactory::buildNewSplendorFromSavefile(const string filename) {
	return XmlReader::getSplendorFromXml(filename);
}