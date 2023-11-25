#include "PlayersUI.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include "CardUI.h"
#include "PlayerNameUI.h"

PlayersUI::PlayersUI(QWidget* parent, QString pname, int nb) : QWidget(parent){
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20*7 + 20*6 +20, 40);
	QHBoxLayout* grid = new QHBoxLayout(this);
	this->setLayout(grid);

	setLayout(grid);
	pgems = new PlayerGemsUI(this);
	QWidget* m = new QWidget(this);
	QGridLayout* g = new QGridLayout(m);
	m->setLayout(g);
	g->setContentsMargins(0, 0, 0, 0);
	g->setSpacing(0);

	for (int i = 0; i < 6; i++) {
		if (i == 5) {
			CardUI* c = new CardUI(m, QString());
			c->ajouterCarte("./Card2.png");
			c->ajouterCarte("./Card3.png");
			g->addWidget(c, 0, i);
		}
		else {
			g->addWidget(new CardUI(m, QString()), 0, i);
		}
	}
	if (nb == 1) {
		grid->addWidget(new PlayerNameUI(pname, this), 1);
		grid->addWidget(pgems, 8);
		grid->addWidget(new QWidget(this), 3);
		grid->addWidget(m, 8);
	}
		
	if (nb == 2) {
		grid->addWidget(m, 8);
		grid->addWidget(new QWidget(this), 3);
		grid->addWidget(pgems, 8);
		grid->addWidget(new PlayerNameUI(pname, this), 1);
	}

	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
}

PlayersUI::~PlayersUI() {
	QWidget::~QWidget();
	delete this->pgems;
}