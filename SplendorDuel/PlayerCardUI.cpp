#include "PlayerCardUI.h"
#include <qgridlayout.h>
#include <qpainter.h>
#include "Image.h"

PlayerCardUI::PlayerCardUI(QWidget* parent) : GemmesContainerGUI(parent) {
	this->cards = new CardUI * [6]();
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20 * 6, 30);
	QGridLayout* g = new QGridLayout(this);
	this->setLayout(g);
	g->setContentsMargins(0, 0, 0, 0);
	g->setSpacing(0);

	for (int i = 0; i < 6; i++) {
		CardUI* c = new CardUI(this);
		g->addWidget(c, 0, i);
		cards[i] = c;
	}

}

PlayerCardUI::~PlayerCardUI() {
	delete[] cards;
	QWidget::~QWidget();
}

void PlayerCardUI::paintEvent(QPaintEvent* event) {
	//on peint la case de transparent
	QPainter painter(this);
	QPixmap pix = Image::getPlayerGems();
	for (int i = 0; i < 6; i++) {
		painter.drawPixmap(width() / 6 * i, 0, width() / 6, height(), pix);
	}
}

void PlayerCardUI::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	//on force que les gemmes soit carrer ou au moins width > height/2
	int min = qMin(width() / 6, height() / 3 * 2);
	resize(min * 6, min / 2 * 3);
	this->update();
}