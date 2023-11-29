#include "PlayersUI.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include "CardUI.h"

PlayersUI::PlayersUI(QWidget* parent, Player* p, int nb) : QWidget(parent), p(p) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20*7 + 20*6 +20, 40);
	QHBoxLayout* grid = new QHBoxLayout(this);
	this->setLayout(grid);

	setLayout(grid);
	pgems = new PlayerGemsUI(this, nb);
	this->pcard = new PlayerCardUI(this);
	this->name = new PlayerNameUI(QString(p->getName().c_str()), this);
	this->points = new PlayerPoints(this);
	if (nb == 1) {
		grid->addWidget(name, 1);
		grid->addWidget(pgems, 8);
		grid->addWidget(points, 3);
		grid->addWidget(pcard, 8);
	}
		
	if (nb == 2) {
		grid->addWidget(pcard, 8);
		grid->addWidget(points, 3);
		grid->addWidget(pgems, 8);
		grid->addWidget(name, 1);
	}

	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
}

PlayersUI::~PlayersUI() {
	QWidget::~QWidget();
	delete this->pgems;
	delete this->pcard;
	delete this->name;
}

void PlayersUI::ajouterCarte(const Card* c) {
	pcard->addCarte(c);
}

/// <summary>
	/// retire 1 a la gems
	/// </summary>
	/// <param name="g">la gems</param>
void PlayersUI::setGemmes() {
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		pgems->setGems(static_cast<Gemmes>(i), p->nbOfGems(static_cast<Gemmes>(i)));
	}
	if (p->getNBGemmes() > 10) {
		pgems->bigError();
	}
}