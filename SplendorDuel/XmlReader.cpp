#include"XmlReader.h"

string XmlReader::language = "fr";

Card* readCard(xml_node<>* card_node) {
	string imageSrc = card_node->first_attribute("image")->value();
	unsigned int prestige;
	sscanf(card_node->first_attribute("prestige")->value(), "%u", &prestige);
	unsigned int bonus;
	sscanf(card_node->first_attribute("discountType")->value(), "%u", &bonus);
	unsigned int nbBonus;
	sscanf(card_node->first_attribute("discount")->value(), "%u", &nbBonus);
	unsigned int crowns;
	sscanf(card_node->first_attribute("crowns")->value(), "%u", &crowns);
	unsigned int level;
	sscanf(card_node->first_attribute("level")->value(), "%u", &level);

	QList<EnumAction> effect{};
	for (xml_node<>* effect_node = card_node->first_node("effects")->first_node("effect"); effect_node; effect_node = effect_node->next_sibling()) {
		unsigned int action;
		sscanf(effect_node->first_attribute("effect")->value(), "%u", &action);
		if (action > 0) {
			effect.append(static_cast<EnumAction>(action));
		}
	}

	Card* card = new Card(level, prestige, static_cast<EnumGemmes>(bonus), nbBonus, crowns, imageSrc, effect);

	xml_node<>* cost_node = card_node->first_node("cost");

	unsigned int cost;
	sscanf(cost_node->first_attribute("vert")->value(), "%u", &cost);
	card->setCost(EnumGemmes::Vert, cost);
	sscanf(cost_node->first_attribute("rouge")->value(), "%u", &cost);
	card->setCost(EnumGemmes::Rouge, cost);
	sscanf(cost_node->first_attribute("bleu")->value(), "%u", &cost);
	card->setCost(EnumGemmes::Bleu, cost);
	sscanf(cost_node->first_attribute("noir")->value(), "%u", &cost);
	card->setCost(EnumGemmes::Noir, cost);
	sscanf(cost_node->first_attribute("blanc")->value(), "%u", &cost);
	card->setCost(EnumGemmes::Blanc, cost);
	sscanf(cost_node->first_attribute("perle")->value(), "%u", &cost);
	card->setCost(EnumGemmes::Perle, cost);

	return card;
}

SplendorDuel& XmlReader::getSplendorFromXml(const string filename) {
	file<> xmlFile(filename.c_str());
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());

	xml_node<>* data_node = xml.first_node("data");

	Bag* bag = getBagFromXml(data_node);
	Board* board = getBoardFromXml(data_node);
	DrawPile** drawPiles = getDrawPilesFromXml(data_node);
	Player* player1 = getPlayerFromXml(data_node, 1);
	Player* player2 = getPlayerFromXml(data_node, 2);
	
	SingletonGameHandler& game = SingletonGameHandler::Instanciate(bag, board, drawPiles, player1, player2, false)->getInstance();

	cout << game.player1Joue << "\n";

	game.displayedCards = getDisplayedCardsFromXml(data_node);

	// player1Joue
	sscanf(data_node->first_node("player1Joue")->value(), "%d", &game.player1Joue);
	// mainActionIsDone
	sscanf(data_node->first_node("mainActionIsDone")->value(), "%d", &game.mainActionIsDone);
	int gem_num;
	// typeToPick
	sscanf(data_node->first_node("typeToPick")->value(), "%d", &gem_num);
	game.typeToPick = static_cast<EnumGemmes>(gem_num);
	// toAssign
	xml_node<>* card_node = data_node->first_node("typeToPick")->first_node("card");
	if (card_node) game.toAssign = readCard(card_node);
	// actions
	xml_node<>* actions_node = data_node->first_node("actions");
	for (xml_node<>* action_node = actions_node->first_node("action"); action_node; action_node = action_node->next_sibling()) {
		int num_action;
		sscanf(actions_node->value(), "%d", &num_action);
		game.actions.push_back(static_cast<EnumAction>(num_action));
	}

	SplendorDuel::instanciate(bag, board, drawPiles, player1, player2, false);

	return SplendorDuel::getInstance();
}

list<Card*> XmlReader::getCardsFromXml() {
	list<Card*> cards;

	file<> xmlFile("./res/cards.xml");
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());

	xml_node<>* root_node = xml.first_node("data")->first_node("cards");
	
	for (xml_node<>* card_node = root_node->first_node("card"); card_node; card_node = card_node->next_sibling()) {

		cards.push_back(readCard(card_node));
	}

	return cards;
}

vector<Card*> XmlReader::getNoblesFromXml() {
	vector<Card*> cards{};

	file<> xmlFile("./res/cards.xml");
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());

	xml_node<>* root_node = xml.first_node("data")->first_node("nobles");
	for (xml_node<>* card_node = root_node->first_node("noble"); card_node; card_node = card_node->next_sibling()) {
		string imageSrc = card_node->first_node("image")->value();
		unsigned int prestige;
		sscanf(card_node->first_node("prestige")->value(), "%u", &prestige);

		QList<EnumAction> effect{};
		for (xml_node<>* effect_node = card_node->first_node("effects")->first_node("effect"); effect_node; effect_node = effect_node->next_sibling()) {
			unsigned int action;
			sscanf(effect_node->value(), "%u", &action);
			if (action > 0) {
				effect.append(static_cast<EnumAction>(action));
			}
		}

		Card* card = new Card(0, prestige, static_cast<EnumGemmes>(0), 0, 0, imageSrc, effect);
		cards.push_back(card);
	}
	return cards;
}

Message XmlReader::getActionMessage(const EnumAction a) {
	file<> xmlFile("./res/message.xml");
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());
	xml_node<>* root_node = xml.first_node("data")->first_node(XmlReader::language.c_str());
	switch (a)
	{
	case EnumAction::ASSIGN_CARD:
		root_node = root_node->first_node("ASSIGN_CARD");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	case EnumAction::SUPP_GEMS:
		root_node = root_node->first_node("SUPP_GEMS");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	case EnumAction::USE_PRIVILEGE:
		root_node = root_node->first_node("USE_PRIVILEGE");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	case EnumAction::PICK_GEMMES:
		root_node = root_node->first_node("PICK_GEMMES");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	case EnumAction::STEAL_GEMMES:
		root_node = root_node->first_node("STEAL_GEMMES");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	case EnumAction::RESERV_CARD:
		root_node = root_node->first_node("RESERV_CARD");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	case EnumAction::REPLAY:
		root_node = root_node->first_node("REPLAY");
		return Message(root_node->first_node("message")->value(), root_node->first_node("color")->value());
	default:
		return Message("", "#ffffff");
	}
}

QList<string> XmlReader::getLanguage() {
	file<> xmlFile("./res/message.xml");
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());
	xml_node<>* root_node = xml.first_node("data");

	QList<string> language{};
	for (xml_node<>* effect_node = root_node->first_node("lang"); effect_node; effect_node = effect_node->next_sibling()) {
		language.append(effect_node->value());
	}
	return language;
}

Bag* XmlReader::getBagFromXml(const xml_node<>* data) {
	Bag* bag;
	
	xml_node<>* bag_node = data->first_node("bag");

	int tailleMax;
	sscanf(bag_node->first_attribute("tailleMax")->value(), "%d", &tailleMax);
	bag = new Bag(tailleMax);

	for (int gem_num = 0; gem_num < NB_GEMMES_PAS_VIDE; gem_num++) {
		EnumGemmes gem = static_cast<EnumGemmes>(gem_num);
		int nb;
		sscanf(bag_node->first_attribute(gemmesToStr(gem).c_str())->value(), "%d", &nb);
		bag->addGemmes(gem, nb);
	}

	bag->melanger();
	return bag;
}

Board* XmlReader::getBoardFromXml(const xml_node<>* data) {
	Board* board = new Board();

	xml_node<>* board_node = data->first_node("board");

	for (xml_node<>* pos_node = board_node->first_node("pos"); pos_node; pos_node = pos_node->next_sibling()) {
		int pos;
		sscanf(pos_node->first_attribute("pos")->value(), "%d", &pos);
		int gem;
		sscanf(pos_node->first_attribute("gem")->value(), "%d", &gem);
		board->putGem(pos, static_cast<EnumGemmes>(gem));
	}

	return board;
}

DrawPile** XmlReader::getDrawPilesFromXml(const xml_node<>* data) {
	DrawPile** drawPiles = new DrawPile*[3];

	xml_node<>* drawPiles_node = data->first_node("drawPiles");


	int cpt = 0;
	for (xml_node<>* drawPile_node = drawPiles_node->first_node("drawPile"); drawPile_node; drawPile_node = drawPile_node->next_sibling()) {

		int taille;
		sscanf(drawPile_node->first_attribute("taille")->value(), "%d", &taille);
		drawPiles[cpt] = new DrawPile(taille);

		for (xml_node<>* card_node = drawPile_node->first_node("card"); card_node; card_node = card_node->next_sibling()) {
			drawPiles[cpt]->deposer(readCard(card_node));
		}
		drawPiles[cpt]->melanger();
		cpt++;
	}

	return drawPiles;
}

Player* XmlReader::getPlayerFromXml(const xml_node<>* data, int pos) {
	Player* player;

	xml_node<>* player_node = data->first_node("player");
	for (int i = 1; i < pos; i++) player_node = player_node->next_sibling();

	char* name;
	sscanf(player_node->first_attribute("name")->value(), "%s", name);

	player = new Player(name);

	int nbCartesReservees;
	sscanf(player_node->first_attribute("nbCartesReservees")->value(), "%d", &nbCartesReservees);
	player->addCarteReservees(nbCartesReservees);

	for (xml_node<>* card_node = player_node->first_node("cards")->first_node("card"); card_node; card_node = card_node->next_sibling()) {
		player->cards.push_back(readCard(card_node));
	}

	xml_node<>* gems_node = player_node->first_node("gems");
	int gems;
	sscanf(gems_node->first_attribute("vert")->value(), "%u", &gems);
	player->addGems(EnumGemmes::Vert, gems);
	sscanf(gems_node->first_attribute("rouge")->value(), "%u", &gems);
	player->addGems(EnumGemmes::Rouge, gems);
	sscanf(gems_node->first_attribute("bleu")->value(), "%u", &gems);
	player->addGems(EnumGemmes::Bleu, gems);
	sscanf(gems_node->first_attribute("noir")->value(), "%u", &gems);
	player->addGems(EnumGemmes::Noir, gems);
	sscanf(gems_node->first_attribute("blanc")->value(), "%u", &gems);
	player->addGems(EnumGemmes::Blanc, gems);
	sscanf(gems_node->first_attribute("perle")->value(), "%u", &gems);
	player->addGems(EnumGemmes::Perle, gems);

	printf("%s", player->name);

	return player;
}

vector<vector<Card*>> XmlReader::getDisplayedCardsFromXml(xml_node<>* data) {
	vector<vector<Card*>> displayedCards;
	xml_node<>* diplayedCards_node = data->first_node("displayedCards");

	for (xml_node<>* cardRow_node = diplayedCards_node->first_node("cardRow"); cardRow_node; cardRow_node = cardRow_node->next_sibling()) {
		displayedCards.push_back(vector<Card*>());
		int i;
		sscanf(cardRow_node->first_attribute("level")->value(), "%d", &i);
		for (xml_node<>* card_node = cardRow_node->first_node("card"); card_node; card_node = card_node->next_sibling()) {
			displayedCards.at(i).push_back(readCard(card_node));
		}
	}

	return displayedCards;
}