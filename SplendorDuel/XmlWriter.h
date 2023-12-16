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
	static void createSaveFile();

private:
	static void savePlayer(xml_document<>& xmldoc, const Player& player);
};

#endif
