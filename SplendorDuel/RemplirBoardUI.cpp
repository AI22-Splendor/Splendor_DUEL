#include "RemplirBoardUI.h"
#include <qpainter.h>
#include <qevent.h>
#include "Image.h"
#include "GameHandler.h"
#include "CompleteBoardUI.h"
#include "SplendorDuel.h"

RemplirBoardUI::RemplirBoardUI(QWidget* parent) : QWidget(parent), hover(false) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(QSize(50*5, 50));
	setMaximumWidth(parent->width());
	setMouseTracking(true);
}


void RemplirBoardUI::mousePressEvent(QMouseEvent* mouse) {
	if (hover) {
		((CompleteBoardUI*)parentWidget())->remplirBoard(SingletonGameHandler::getInstance().remplirBoard());
		SplendorDuel::refreshPrivilege();
	}
}

void RemplirBoardUI::leaveEvent(QEvent* event) {
	if (hover) {
		hover = false;
		update();
	}
}

void RemplirBoardUI::mouseMoveEvent(QMouseEvent* mouse){
	QWidget::mouseMoveEvent(mouse);
	if (hover) {
		if (mouse->x() < width() / 2 - height() / 2 || mouse->x() > width() / 2 + height() / 2) {
			this->hover = false;
			this->update();
		}
	}
	else {
		if (mouse->x() > (width() / 2 - height() / 2) && mouse->x() < (width() / 2 + height() / 2)) {
			this->hover = true;
			this->update();
		}
	}
}


void RemplirBoardUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QPixmap pix = Image::getUnderPlateau();
	painter.drawPixmap(0, 0, width(), height(), pix);
	//si hover on fait grossir l'image de remplir
	QPixmap x = Image::getRemplir();
	if (hover) {
		painter.drawPixmap(width()/2-height()/2, 0, height(), height(), x);
	}
	else {
		painter.drawPixmap(width() / 2- height() / 10 * 4, height() / 8, height()/10*8, height()/8*6, x);
	}
}

void RemplirBoardUI::resizeEvent(QResizeEvent* event) {
	// Appelez la fonction de base pour que l'événement soit correctement traité
	QWidget::resizeEvent(event);
	// Forcer un nouveau rendu lorsque la taille change
	update();
}