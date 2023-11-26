#include "BoardCard.h"
#include <qgridlayout.h>

BoardCardUI::BoardCardUI(QWidget* parent) : GemmesContainerGUI(parent) {
	this->cards = new CardUI **[3]();
	this->cards[0] = new CardUI *[6]();
	this->cards[1] = new CardUI * [6]();
	this->cards[2] = new CardUI * [6]();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20 * 6, 30*3);
	QGridLayout* g = new QGridLayout(this);
	this->setLayout(g);

	g->setContentsMargins(0, 0, 0, 0);
	g->setSpacing(0);

	for (int i = 0; i < 6; i++) {
		
	}
}

BoardCardUI::~BoardCardUI() {
	for (int i = 0; i < 3; i++) {
		delete[] this->cards[i];
	}
	delete[] cards;
	QWidget::~QWidget();
}