#include "PrivilegeUI.h"
#include "GameHandler.h"
#include <qpainter.h>
#include "Image.h"

PrivilegeUI::PrivilegeUI(QWidget* parent) : QWidget(parent), hover(false), havePrivilege(true) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void PrivilegeUI::mousePressEvent(QMouseEvent* event) {
	if (havePrivilege && GameHandler::getInstance().playPrivilege()) {
		havePrivilege = false;
		update();
	}
}

void PrivilegeUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	if (hover) {
		//painter.drawPixmap(0, 0, width(), height(), Image::getPixmap(Gemmes::Blanc));
	}
	else if (havePrivilege) {
		//painter.drawPixmap(width() / 5, height() / 5, width() / 5 * 3, height() / 5 * 3, Image::getPixmap(Gemmes::Blanc));
	}
	else {
		//painter.drawPixmap(width()/5, height()/5, width()/5*3, height()/5*3, Image::getPixmap(Gemmes::Blanc));
		QColor color(Qt::black);
		color.setAlpha(99);
	}
}

void PrivilegeUI::leaveEvent(QEvent* event) {
	if (hover) {
		hover = false;
		update();
	}
}

void PrivilegeUI::enterEvent(QEnterEvent* event) {
	if (!hover && havePrivilege) {
		hover = true;
		update();
	}
}