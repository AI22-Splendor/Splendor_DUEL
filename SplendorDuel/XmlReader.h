#ifndef XMLREADER_H
#define XMLREADER_H

// Library imports here to avoid redondancy
#include "./libs/rapidxml-1.13/rapidxml.hpp"
#include "./libs/rapidxml-1.13/rapidxml_utils.hpp"

#include "Action.h"
#include "Card.h"
#include "Message.h"


class XmlReader {
public:
	static list<Card*> getCardsFromXml();

	static vector<Card*> getNoblesFromXml();

	static Message getActionMessage(const EnumAction a);
	static inline void setLanguage(string s) { XmlReader::language = s; }
	static QList<string> getLanguage();
private:
	static string language;
};

#endif