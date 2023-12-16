#include "XmlReader.h"
#include <qlist.h>

using namespace rapidxml;

string XmlReader::language = "fr";

list<Card*> XmlReader::getCardsFromXml() {
	list<Card*> cards;

	file<> xmlFile("./res/cards.xml");
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());

	xml_node<>* root_node = xml.first_node("data")->first_node("cards");

	int cpt = 0;
	// Iterate over the brewerys
	for (xml_node<>* card_node = root_node->first_node("card"); card_node; card_node = card_node->next_sibling()) {
		
		string imageSrc = card_node->first_node("image")->value();
		unsigned int prestige;
		sscanf(card_node->first_node("prestige")->value(), "%u", &prestige);
		unsigned int bonus;
		sscanf(card_node->first_node("discountType")->value(), "%u", &bonus);
		unsigned int nbBonus;
		sscanf(card_node->first_node("discount")->value(), "%u", &nbBonus);
		unsigned int crowns;
		sscanf(card_node->first_node("crowns")->value(), "%u", &crowns);
		unsigned int level;
		sscanf(card_node->first_node("level")->value(), "%u", &level);

		QList<EnumAction> effect{};
		for (xml_node<>* effect_node = card_node->first_node("effects")->first_node("effect"); effect_node; effect_node = effect_node->next_sibling()) {
			unsigned int action;
			sscanf(effect_node->value(), "%u", &action);
			if (action > 0) {
				effect.append(static_cast<EnumAction>(action));
			}
		}

		Card* card = new Card(level, prestige, static_cast<EnumGemmes>(bonus), nbBonus, crowns, imageSrc, effect);

		xml_node<>* cost_node = card_node->first_node("cost");

		unsigned int cost;
		sscanf(cost_node->first_node("vert")->value(), "%u", &cost);
		card->setCost(EnumGemmes::Vert, cost);
		sscanf(cost_node->first_node("rouge")->value(), "%u", &cost);
		card->setCost(EnumGemmes::Rouge, cost);
		sscanf(cost_node->first_node("bleu")->value(), "%u", &cost);
		card->setCost(EnumGemmes::Bleu, cost);
		sscanf(cost_node->first_node("noir")->value(), "%u", &cost);
		card->setCost(EnumGemmes::Noir, cost);
		sscanf(cost_node->first_node("blanc")->value(), "%u", &cost);
		card->setCost(EnumGemmes::Blanc, cost);
		sscanf(cost_node->first_node("perle")->value(), "%u", &cost);
		card->setCost(EnumGemmes::Perle, cost);

		cards.push_back(card);
		cpt++;
	}

	return cards;
}

vector<Card*> XmlReader::getNoblesFromXml() {
	vector<Card*> cards{};

	file<> xmlFile("./res/cards.xml");
	xml_document<> xml;
	xml.parse<0>(xmlFile.data());

	xml_node<>* root_node = xml.first_node("data")->first_node("nobles");
	// Iterate over the brewerys
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