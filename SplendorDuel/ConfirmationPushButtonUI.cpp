#include "ConfirmationPushButtonUI.h"
#include "Image.h"
#include <qpainter.h>
ConfirmationPushButtonUI::ConfirmationPushButtonUI(QWidget* parent) : hover(false), QPushButton(parent) {

}

void ConfirmationPushButtonUI::paintEvent(QPaintEvent* e) {
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setMinimumSize(10, 10);
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	if (hover) {
		QColor c("#000000");
		c.setAlpha(99);
		painter.setBrush(c);
		painter.drawRect(0, 0, width(), height());
	}
	else {
		QColor c("#000000");
		c.setAlpha(99);
		painter.setBrush(c);
		painter.drawRect(width() / 10, height() / 10, width() / 10 * 8, height() / 10 * 8);
	}
	QFont font = painter.font();
	int min = qMin(width(), height());
	font.setPointSize(min / 7);
	painter.setFont(font);
	painter.setPen(QColor("#ffffff"));
	QRect drawRect(0, 0, width(), height());
	painter.drawText(drawRect, Qt::AlignCenter, "Valider");
}