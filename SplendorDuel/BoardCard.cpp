#include "BoardCard.h"
#include <qgridlayout.h>

BoardCardUI::BoardCardUI(QWidget* parent) : GemmesContainerGUI(parent) {
	this->cards = new CardUI **[3]();
	this->cards[0] = new CardUI *[3]();
	this->cards[1] = new CardUI * [4]();
	this->cards[2] = new CardUI * [5]();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20 * 6, 30*3);
	QGridLayout* g = new QGridLayout(this);
	this->setLayout(g);
	for (int i = 0; i < 3; i++) {
		QString s = "./res/";
		s.append(QString::number(3-i));
		s.append(QString(".png"));
		CardUI* c = new CardUI(this, s);
		g->addWidget(c, i, 0);
		for (int i = 0; i < 11; i++) {
			QString s = "./res/Blanc";
			s.append(QString::number(i));
			s.append(QString(".png"));
			c->ajouterCarte(s);
		}
	}
	for (int i = 0; i < 3; i++) {
		CardUI* c = new CardUI(this, QString("./res/Card1.png"));
		g->addWidget(c, 0, i+3);
	}

	for (int i = 0; i < 4; i++) {
		CardUI* c = new CardUI(this, QString("./res/Card3.png"));
		g->addWidget(c, 1, i+2);
	}

	for (int i = 0; i < 5; i++) {
		CardUI* c = new CardUI(this, QString("./res/Card2.png"));
		g->addWidget(c, 2, i+1);
	}

	g->setContentsMargins(0, 0, 0, 0);
	g->setSpacing(0);
}

BoardCardUI::~BoardCardUI() {
	for (int i = 0; i < 3; i++) {
		delete[] this->cards[i];
	}
	delete[] cards;
	QWidget::~QWidget();
}