#include "PersonnageBoardUI.h"
#include <qgridlayout.h>
PersonnageBoardUI::PersonnageBoardUI(QWidget* parent): CardContainersGUI(parent) {
	cards = new CardUI*[4];
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QGridLayout* grid = new QGridLayout();
	grid->setSpacing(0);
	grid->getContentsMargins(0, 0, 0, 0);
	this->setLayout(grid);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			grid->addWidget(new CardUI(this), i, j);
		}
	}
}

PersonnageBoardUI::~PersonnageBoardUI() {
	delete[] cards;
}