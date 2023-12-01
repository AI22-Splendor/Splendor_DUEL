#include "PrivilegeBoardUI.h"
#include <qpainter.h>
#include <qgridlayout.h>
#include "PrivilegeUI.h"

PrivilegeBoardUI::PrivilegeBoardUI(QWidget* parent): QWidget(parent) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setMinimumSize(50, 100);
	QVBoxLayout* vlayout = new QVBoxLayout(this);
	this->setLayout(vlayout);
	vlayout->setSpacing(0);
	vlayout->setContentsMargins(0, 0, 0, 0);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			vlayout->addWidget(new PrivilegeUI(this));
		}
	}
}

PrivilegeBoardUI::~PrivilegeBoardUI() {

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