#ifndef XMLWRITER_H
#define XMLWRITER_H

#include "GameHandler.h"

#include "./libs/rapidxml-1.13/rapidxml.hpp"
#include "./libs/rapidxml-1.13/rapidxml_utils.hpp"
#include "./libs/rapidxml-1.13/rapidxml_print.hpp"

using namespace rapidxml;
using namespace std;

class XmlWriter {
public:
	static void createSaveFile(const string filename);

private:
	static char* int2char(xml_document<>& xmldoc, const int value);
	static char* bool2char(xml_document<>& xmldoc, const bool value);

	static xml_node<>* savePlayer(xml_document<>& xmldoc, const Player& player);
	static xml_node<>* saveCard(xml_document<>& xmldoc, const Card& card);
	static xml_node<>* saveBag(xml_document<>& xmldoc, const Bag& bag);
	static xml_node<>* saveBoard(xml_document<>& xmldoc, const Board& board);
	static xml_node<>* saveDisplayedCards(xml_document<>& xmldoc, const vector<vector<Card*>>& displayedCards);
	static xml_node<>* saveDrawPiles(xml_document<>& xmldoc, DrawPile** drawPiles);
};

#endif
