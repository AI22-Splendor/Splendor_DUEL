#ifndef XMLREADER_H
#define XMLREADER_H

// Library imports here to avoid redondancy
#include "./libs/rapidxml-1.13/rapidxml.hpp"
#include "./libs/rapidxml-1.13/rapidxml_utils.hpp"

#include <qlist.h>
#include "XmlReader.h"
#include "SplendorDuel.h"
#include "Action.h"
#include "Card.h"
#include "Message.h"

using namespace rapidxml;

class XmlReader {
public:
	static SplendorDuel& getSplendorFromXml(const string filename);

	static list<Card*> getCardsFromXml();

	static vector<Card*> getNoblesFromXml();

	static Message getActionMessage(const EnumAction a);
	static inline void setLanguage(string s) { XmlReader::language = s; }
	static QList<string> getLanguage();
private:
	static Bag* getBagFromXml(const xml_node<>* data);
	static Board* getBoardFromXml(const xml_node<>* data);
	static DrawPile** getDrawPilesFromXml(const xml_node<>* data);
	static Player* getPlayerFromXml(const xml_node<>* data, int pos);
	static vector<vector<Card*>> getDisplayedCardsFromXml(xml_node<>* data);
	static void instanciatePrivilegesFromXml(xml_node<>* data);
	static void instanciateNoblesFromXml(xml_node<>* data);

	static string language;
};

#endif