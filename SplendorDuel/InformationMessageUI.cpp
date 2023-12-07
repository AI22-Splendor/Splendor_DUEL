#include "InformationMessageUI.h"
#include <qpainter.h>

InformationMessageUI::InformationMessageUI(QWidget* parent) : QWidget(parent), message(Message("", "")) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20, 20);
}

void InformationMessageUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	QFont font = painter.font();
	if (message.getString().length() > 0) {
		font.setPointSize(width()/ message.getString().length()*1.5);
		QColor c("#ffffff");
		painter.setFont(font);
		painter.setPen(message.getColor());
		QRect drawRect(0, 0, width(), height());
		painter.drawText(drawRect, Qt::AlignCenter, message.getString());
	}
}