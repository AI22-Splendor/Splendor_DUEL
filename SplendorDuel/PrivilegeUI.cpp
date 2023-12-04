#include "PrivilegeUI.h"
#include "GameHandler.h"
#include <qpainter.h>
#include "Image.h"

PrivilegeUI::PrivilegeUI(QWidget* parent, int pnum) : pnum(pnum), QWidget(parent), hover(false), havePrivilege(false) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void PrivilegeUI::mousePressEvent(QMouseEvent* event) {
	if (havePrivilege && ((pnum==0 && GameHandler::getInstance().isPlayer1Turn()) || (pnum==1 && !GameHandler::getInstance().isPlayer1Turn())) && GameHandler::getInstance().playPrivilege()) {
		havePrivilege = false;
		update();
	}
}

void PrivilegeUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	if (hover && havePrivilege) {
		painter.drawPixmap(0, 0, width(), height(), Image::getPixmap(Gemmes::Blanc));
	}
	else if (havePrivilege) {
		painter.drawPixmap(width() / 5, height() / 5, width() / 5 * 3, height() / 5 * 3, Image::getPixmap(Gemmes::Blanc));
	}
	else {
		painter.drawPixmap(width()/5, height()/5, width()/5*3, height()/5*3, Image::getPixmap(Gemmes::Blanc));
		QColor color(Qt::black);
		color.setAlpha(99);
		painter.setBrush(color);
		painter.setPen(Qt::NoPen);
		painter.drawRect(width() / 5, height() / 5, width() / 5 * 3, height() / 5 * 3);
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