#include "BoardCompleteUI.h"
#include <qpainter.h>
#include <qevent.h>
#include "Image.h"
BoardComplete::BoardComplete(QWidget* parent) : QWidget(parent) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setMinimumSize(QSize(50, 50));
}


void BoardComplete::mousePressEvent(QMouseEvent* mouse) {

}

void BoardComplete::enterEvent(QEnterEvent* event) {

}

void BoardComplete::leaveEvent(QEvent* event) {

}

void BoardComplete::paintEvent(QPaintEvent* event) {
	//on peint la case de transparent
	QPainter painter(this);
	QPixmap pix = Image::getUnderPlateau();
	

	//on dessinne maintenant l'image au centre
	painter.drawPixmap(0, 0, width(), height(), pix);

}

void BoardComplete::resizeEvent(QResizeEvent* event) {
	// Appelez la fonction de base pour que l'événement soit correctement traité
	QWidget::resizeEvent(event);
	// Forcer un nouveau rendu lorsque la taille change
	update();
}