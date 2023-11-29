#include "XmlReader.h"

using namespace rapidxml;

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

		for (xml_node<>* effect_node = card_node->first_node("effects")->first_node("effect"); effect_node; effect_node = effect_node->next_sibling()) {
			// TODO
		}

		Card* card = new Card(level, prestige, static_cast<Gemmes>(bonus), nbBonus, crowns, imageSrc);

		xml_node<>* cost_node = card_node->first_node("cost");

		unsigned int cost;
		sscanf(cost_node->first_node("vert")->value(), "%u", &cost);
		card->setCost(Gemmes::Vert, cost);
		sscanf(cost_node->first_node("rouge")->value(), "%u", &cost);
		card->setCost(Gemmes::Rouge, cost);
		sscanf(cost_node->first_node("bleu")->value(), "%u", &cost);
		card->setCost(Gemmes::Bleu, cost);
		sscanf(cost_node->first_node("noir")->value(), "%u", &cost);
		card->setCost(Gemmes::Noir, cost);
		sscanf(cost_node->first_node("blanc")->value(), "%u", &cost);
		card->setCost(Gemmes::Blanc, cost);
		sscanf(cost_node->first_node("perle")->value(), "%u", &cost);
		card->setCost(Gemmes::Perle, cost);

		cards.push_back(card);
		cpt++;
	}

	return cards;
}