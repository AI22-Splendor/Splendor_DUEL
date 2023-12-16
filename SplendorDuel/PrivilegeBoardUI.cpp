#include "PrivilegeBoardUI.h"
#include <qpainter.h>
#include <qgridlayout.h>
#include "GameHandler.h"


PrivilegeBoardUI::PrivilegeBoardUI(QWidget* parent): QWidget(parent) {
	tab = new PrivilegeUI * *[2]();
	for (int i = 0; i < 2; i++) {
		tab[i] = new PrivilegeUI * [3]();
	}
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setMinimumSize(50, 100);
	QVBoxLayout* vlayout = new QVBoxLayout(this);
	this->setLayout(vlayout);
	vlayout->setSpacing(0);
	vlayout->setContentsMargins(0, 0, 0, 0);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			tab[i][j] = new PrivilegeUI(this, i);
			vlayout->addWidget(tab[i][j]);
		}
	}
}

PrivilegeBoardUI::~PrivilegeBoardUI() {
	for (int i = 0; i < 2; i++) {
		delete[] tab[i];
	}
	delete[] tab;
}

void PrivilegeBoardUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, width(), height(), QPixmap("./res/playerFond.png"));
	painter.setBrush(QColor(Qt::black));
	painter.setPen(Qt::black);
	painter.drawRect(0, (height() / 2) - 5, width(), 10);
}
void PrivilegeBoardUI::resizeEvent(QResizeEvent* event) {

}

void PrivilegeBoardUI::refreshPrivilege(){
	for (int i = 0; i < 2; i++) {
		int nb = SingletonGameHandler::getInstance().getPlayerNbPrivilege(i);

		for (int j = 0; j < 3; j++) {
			tab[i][j]->setPrivilege((j < nb));
		}
	}
}