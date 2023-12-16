#include "XmlWriter.h"

void XmlWriter::createSaveFile() {

	xml_document<> xmldoc;

	xml_node<>* decl = xmldoc.allocate_node(node_declaration);
	decl->append_attribute(xmldoc.allocate_attribute("version", "1.0"));
	decl->append_attribute(xmldoc.allocate_attribute("encoding", "utf-8"));
	xmldoc.append_node(decl);


	SingletonGameHandler& game = SingletonGameHandler::getInstance();
	savePlayer(xmldoc, *game.player1);
	savePlayer(xmldoc, *game.player2);
	/*game.player1Joue;
	game.bag;
	game.board;
	game.action;
	game.displayedCards;
	game.drawPiles;
	game.mainActionIsDone;
	game.toAssign;
	game.typeToPick;*/


	ofstream file;
	file.open("./res/savefile.xml");
	file.clear();

	file << xmldoc;

	file.close();
	xmldoc.clear();
} 

void XmlWriter::savePlayer(xml_document<>& xmldoc,const Player	& player) {
	xml_node<>* playerNode = xmldoc.allocate_node(node_element, "Player");
	
	playerNode->append_attribute(xmldoc.allocate_attribute("Name", xmldoc.allocate_string(player.getName().c_str())));

	xmldoc.append_node(playerNode);
}