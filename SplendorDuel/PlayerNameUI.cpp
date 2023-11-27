#include "PlayerNameUI.h"
#include <qpainter.h>
#include "Image.h"

void PlayerNameUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);

	//si c'est son tour
	if (tour) {
		QColor c("#ffff66");
		c.setAlpha(99);
		painter.setBrush(c);
	}
	else {
		QColor c("#454545");
		c.setAlpha(99);
		painter.setBrush(c);
	}
	painter.drawRect(0, 0, width(), height());
	QFont font = painter.font();
	font.setPointSize(width() / name.length());
	painter.setFont(font);
	painter.setPen(QColor("#ffffff"));
	QRect drawRect(0, 0, width(), height());
	painter.drawText(drawRect, Qt::AlignCenter, name);
}

void PlayerNameUI::resizeEvent(QResizeEvent* event) {
	// Appelez la fonction de base pour que l'événement soit correctement traité
	QWidget::resizeEvent(event);
	// Forcer un nouveau rendu lorsque la taille change
	update();
}
