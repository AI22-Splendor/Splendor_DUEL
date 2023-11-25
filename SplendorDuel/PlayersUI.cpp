#include "PlayersUI.h"
#include <qgridlayout.h>

PlayersUI::PlayersUI(QWidget* parent, int player) : QWidget(parent), player(player) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	QHBoxLayout* grid = new QHBoxLayout(this);
	setLayout(grid);
	pgems = new PlayerGemsUI(this);
	grid->addWidget(pgems, 3);

	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
}

PlayersUI::~PlayersUI() {
	QWidget::~QWidget();
	delete this->pgems;
}