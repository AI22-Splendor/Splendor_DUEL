#include "PersonnageBoardUI.h"
#include <qgridlayout.h>
#include "XmlReader.h"
#include "NobleHandler.h"

PersonnageBoardUI::PersonnageBoardUI(QWidget* parent): CardContainersGUI(parent) {
	cards = new CardUI*[4]();
	// TODO CHANGER
	vector<Card*> nobles = NobleHandler::getInstance()->getNobleCards();
	int i = 0;
	for (Card* c: nobles) {
		cards[i] = new CardUI(this, 0, i);
		cards[i]->ajouterCarte(c);
		i++;
	}
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QGridLayout* grid = new QGridLayout();
	grid->setSpacing(0);
	grid->getContentsMargins(0, 0, 0, 0);
	this->setLayout(grid);
	int ligne = 0;
	for (int i = 0; i < 4; i++) {
		if (i == 2)
			ligne++;
		grid->addWidget(cards[i], i%2, ligne);
	}
}

PersonnageBoardUI::~PersonnageBoardUI() {
	delete[] cards;
}

void PersonnageBoardUI::clickCard(int col, int ligne, Card* c) {
	if (GameHandler::getInstance().buyNoble(c)) {
		cards[col]->supprimerCarte(c);
		cards[col] = nullptr;
	}
	else {
		this->cards[col]->showErr();
	}

}