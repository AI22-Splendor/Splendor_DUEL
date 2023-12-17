#include "XmlWriter.h"

char* XmlWriter::int2char(xml_document<>& xmldoc, const int value) {
	char tmpval[64];
	sprintf(tmpval, "%d", value);
	return xmldoc.allocate_string(tmpval);
}
char* XmlWriter::bool2char(xml_document<>& xmldoc, const bool value) {
	char tmpval[64];
	sprintf(tmpval, "%d", value ? 1 : 0);
	return xmldoc.allocate_string(tmpval);
}

void XmlWriter::createSaveFile(const string filename) {

	xml_document<> xmldoc;

	xml_node<>* decl = xmldoc.allocate_node(node_declaration);
	decl->append_attribute(xmldoc.allocate_attribute("version", "1.0"));
	decl->append_attribute(xmldoc.allocate_attribute("encoding", "utf-8"));
	xmldoc.append_node(decl);

	xml_node<>* data = xmldoc.allocate_node(node_element, "data");

	SingletonGameHandler& game = SingletonGameHandler::getInstance();

	xml_node<>* player1JoueNode = xmldoc.allocate_node(node_element, "player1Joue", bool2char(xmldoc, game.player1Joue));
	data->append_node(player1JoueNode);

	xml_node<>* actionsNode = xmldoc.allocate_node(node_element, "actions");
	for (EnumAction action : game.actions) {
		xml_node<>* actionNode = xmldoc.allocate_node(node_element, "action", int2char(xmldoc, action));
		actionsNode->append_node(actionNode);
	}
	data->append_node(actionsNode);
	
	xml_node<>* mainActionIsDoneNode = xmldoc.allocate_node(node_element, "mainActionIsDone", bool2char(xmldoc, game.mainActionIsDone));
	data->append_node(mainActionIsDoneNode);

	xml_node<>* toAssignNode = xmldoc.allocate_node(node_element, "toAssign");
	if (game.toAssign) toAssignNode->append_node(saveCard(xmldoc, *game.toAssign));
	data->append_node(toAssignNode);

	xml_node<>* typeToPickNode = xmldoc.allocate_node(node_element, "typeToPick", int2char(xmldoc, game.typeToPick));
	data->append_node(typeToPickNode);

	data->append_node(savePlayer(xmldoc, *game.player1));
	data->append_node(savePlayer(xmldoc, *game.player2));

	data->append_node(saveBag(xmldoc, *game.bag));

	data->append_node(saveBoard(xmldoc, *game.board));

	data->append_node(saveDisplayedCards(xmldoc, game.displayedCards));

	data->append_node(saveDrawPiles(xmldoc, game.drawPiles));

	data->append_node(savePrivileges(xmldoc));

	data->append_node(saveNobles(xmldoc));

	xmldoc.append_node(data);

	ofstream file;
	file.open(filename);
	file.clear();

	file << xmldoc;

	file.close();
	xmldoc.clear();
} 


xml_node<>* XmlWriter::saveCard(xml_document<>& xmldoc, const Card& card) {
	xml_node<>* cardNode = xmldoc.allocate_node(node_element, "card");
	
	cardNode->append_attribute(xmldoc.allocate_attribute("image", xmldoc.allocate_string(card.getImageSrc().toLocal8Bit().data())));
	cardNode->append_attribute(xmldoc.allocate_attribute("prestige", int2char(xmldoc, card.getPointsPrestige())));
	cardNode->append_attribute(xmldoc.allocate_attribute("crowns", int2char(xmldoc, card.getCrowns())));
	cardNode->append_attribute(xmldoc.allocate_attribute("discount", int2char(xmldoc, card.getDiscount())));
	cardNode->append_attribute(xmldoc.allocate_attribute("discountType", int2char(xmldoc, card.getDiscountType())));
	cardNode->append_attribute(xmldoc.allocate_attribute("level", int2char(xmldoc, card.getLevel())));
	
	xml_node<>* costNode = xmldoc.allocate_node(node_element, "cost");
	for (int gem_number = 0; gem_number < NB_GEMMES_PAIEMENTS; gem_number++) {
		EnumGemmes gem = static_cast<EnumGemmes>(gem_number);
		costNode->append_attribute(xmldoc.allocate_attribute(xmldoc.allocate_string(gemmesToStr(gem).c_str()), int2char(xmldoc, card.getPriceForGemme(gem))));
	}
	cardNode->append_node(costNode);

	xml_node<>* effectsNode = xmldoc.allocate_node(node_element, "effects");
	for (EnumAction action : card.getEffects()) {
		xml_node<>* effectNode = xmldoc.allocate_node(node_element, "effect");
		effectNode->append_attribute(xmldoc.allocate_attribute("effect", int2char(xmldoc, action)));
		effectsNode->append_node(effectNode);
	}
	cardNode->append_node(effectsNode);

	return cardNode;
}


xml_node<>* XmlWriter::savePlayer(xml_document<>& xmldoc, const Player& player) {
	xml_node<>* playerNode = xmldoc.allocate_node(node_element, "player");
	
	playerNode->append_attribute(xmldoc.allocate_attribute("name", xmldoc.allocate_string(player.getName().c_str())));
	playerNode->append_attribute(xmldoc.allocate_attribute("nbCartesReservees", int2char(xmldoc, player.getNbCarteReservees())));

	xml_node<>* cardsNode = xmldoc.allocate_node(node_element, "cards");
	for (const Card* card : player.getCards()) {
		cardsNode->append_node(saveCard(xmldoc, *card));
	}
	playerNode->append_node(cardsNode);

	xml_node<>* gemsNode = xmldoc.allocate_node(node_element, "gems");
	for (int gem_number = 0; gem_number < NB_GEMMES_PAS_VIDE; gem_number++) {
		EnumGemmes gem = static_cast<EnumGemmes>(gem_number);
		gemsNode->append_attribute(xmldoc.allocate_attribute(xmldoc.allocate_string(gemmesToStr(gem).c_str()), int2char(xmldoc, player.nbOfGems(gem))));
	}
	playerNode->append_node(gemsNode);
	
	return playerNode;
}


xml_node<>* XmlWriter::saveBag(xml_document<>& xmldoc, const Bag& bag) {
	xml_node<>* bagNode = xmldoc.allocate_node(node_element, "bag");

	bagNode->append_attribute(xmldoc.allocate_attribute("tailleMax", int2char(xmldoc, bag.getTaille())));

	for (int gem_num = 0; gem_num < EnumGemmes::Vide; gem_num++) {
		EnumGemmes gem = static_cast<EnumGemmes>(gem_num);
		bagNode->append_attribute(xmldoc.allocate_attribute(xmldoc.allocate_string(gemmesToStr(gem).c_str()), int2char(xmldoc, bag.getNbGemmesType(gem))));
	}

	return bagNode;
}

xml_node<>* XmlWriter::saveBoard(xml_document<>& xmldoc, const Board& board) {
	xml_node<>* boardNode = xmldoc.allocate_node(node_element, "board");

	for (int i = 0; i < board.BOARD_SIZE; i++) {
		if (board.connaitreGemmes(i) != EnumGemmes::Vide) {
			xml_node<>* positionNode = xmldoc.allocate_node(node_element, "pos");
			positionNode->append_attribute(xmldoc.allocate_attribute("pos", int2char(xmldoc, i)));
			positionNode->append_attribute(xmldoc.allocate_attribute("gem", int2char(xmldoc, board.connaitreGemmes(i))));
			boardNode->append_node(positionNode);
		}
	}

	return boardNode;
}

xml_node<>* XmlWriter::saveDisplayedCards(xml_document<>& xmldoc, const vector<vector<Card*>>& displayedCards) {
	xml_node<>* displayedCardsNode = xmldoc.allocate_node(node_element, "displayedCards");

	for (vector<Card*> row : displayedCards) {
		xml_node<>* cardRowNode = xmldoc.allocate_node(node_element, "cardRow");
		cardRowNode->append_attribute(xmldoc.allocate_attribute("level", int2char(xmldoc, row[0]->getLevel())));

		for (Card* card : row) {
			cardRowNode->append_node(saveCard(xmldoc, *card));
		}
		displayedCardsNode->append_node(cardRowNode);
	}
	return displayedCardsNode;
}

xml_node<>* XmlWriter::saveDrawPiles(xml_document<>& xmldoc, DrawPile** drawPiles) {
	xml_node<>* drawPilesNode = xmldoc.allocate_node(node_element, "drawPiles");

	for (int i = 0; i < 3; i++) {
		xml_node<>* drawPileNode = xmldoc.allocate_node(node_element, "drawPile");
		drawPileNode->append_attribute(xmldoc.allocate_attribute("taille", int2char(xmldoc, drawPiles[i]->taille)));

		for (int j = drawPiles[i]->head; j != drawPiles[i]->last; j = (j + 1) % drawPiles[i]->taille) {
			drawPileNode->append_node(saveCard(xmldoc, *drawPiles[i]->pile[j]));
		}
		
		drawPilesNode->append_node(drawPileNode);
	}

	return drawPilesNode;
}

xml_node<>* XmlWriter::savePrivileges(xml_document<>& xmldoc) {
	xml_node<>* privilegesNode = xmldoc.allocate_node(node_element, "privileges");

	for (int i = 0; i < 3; i++) {
		xml_node<>* privilegeNode = xmldoc.allocate_node(node_element, "privilege", 
			int2char(xmldoc, SingletonPrivilegeHandler::getInstance()->emplacementsPrivilege[i]));
		privilegesNode->append_node(privilegeNode);
	}

	return privilegesNode;
}

xml_node<>* XmlWriter::saveNobles(xml_document<>& xmldoc) {
	xml_node<>* noblesNode = xmldoc.allocate_node(node_element, "nobles");

	for (int i = 0; i < 4; i++) {
		xml_node<>* nobleNode = xmldoc.allocate_node(node_element, "noble",
			int2char(xmldoc, SingletonNobleHandler::getInstance()->noblePosition[i]));
		noblesNode->append_node(nobleNode);
	}

	return noblesNode;
}