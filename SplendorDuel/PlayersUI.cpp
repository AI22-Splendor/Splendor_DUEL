#include "PlayersUI.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include "CardUI.h"
#include "PlayerNameUI.h"
#include "PlayerCardUI.h"

PlayersUI::PlayersUI(QWidget* parent, QString pname, int nb) : QWidget(parent){
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20*7 + 20*6 +20, 40);
	QHBoxLayout* grid = new QHBoxLayout(this);
	this->setLayout(grid);

	setLayout(grid);
	pgems = new PlayerGemsUI(this);
	PlayerCardUI* pcard = new PlayerCardUI(this);
	if (nb == 1) {
		grid->addWidget(new PlayerNameUI(pname, this), 1);
		grid->addWidget(pgems, 8);
		grid->addWidget(new QWidget(this), 3);
		grid->addWidget(pcard, 8);
	}
		
	if (nb == 2) {
		grid->addWidget(pcard, 8);
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