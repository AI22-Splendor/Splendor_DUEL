#pragma once
// Library imports here to avoid redondancy
#include "./libs/rapidxml-1.13/rapidxml.hpp"
#include "./libs/rapidxml-1.13/rapidxml_utils.hpp"

#include "Card.h"

class XmlReader {
public:
	static list<Card*> getCardsFromXml();

	// static list<Noble*> getNoblesFromXml();
};

