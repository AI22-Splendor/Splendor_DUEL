#include "PlayerCardUI.h"
#include <qgridlayout.h>

PlayerCardUI::PlayerCardUI(QWidget* parent) : GemmesContainerGUI(parent) {
	this->cards = new CardUI * [6]();
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20 * 6, 30);
	QGridLayout* g = new QGridLayout(this);
	this->setLayout(g);
	g->setContentsMargins(0, 0, 0, 0);
	g->setSpacing(0);

	for (int i = 0; i < 6; i++) {
		if (i == 5) {
			CardUI* c = new CardUI(this, QString("./res/Card1.png"));
			c->ajouterCarte("./res/Card2.png");
			c->ajouterCarte("./res/Card3.png");
			g->addWidget(c, 0, i);
		}
		else {
			g->addWidget(new CardUI(this, QString("./res/1.png")), 0, i);
		}
	}

}

PlayerCardUI::~PlayerCardUI() {
	delete[] cards;
	QWidget::~QWidget();
}