#include "PlayerGemsUI.h"
#include <qpainter.h>
#include <qpixmap.h>
#include "Image.h"
#include <qgridlayout.h>

PlayerGemsUI::PlayerGemsUI(QWidget* parent): GemmesContainerGUI(parent){
	this->gem =new GemmesUI*[7]();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20*7, 20);
	QGridLayout* grid = new QGridLayout(this);
	this->setLayout(grid);
	for (int i = 0; i < 7; i++) {
			GemmesUI* boutton = new GemmesUI(i, -1, this);
			switch (i)
			{
			case 0:
				boutton->setGemmes(Gemmes::Vert);
				break;
			case 1:
				boutton->setGemmes(Gemmes::Rouge);
				break;
			case 2:
				boutton->setGemmes(Gemmes::Bleu);
				break;
			case 3:
				boutton->setGemmes(Gemmes::Noir);
				break;
			case 4:
				boutton->setGemmes(Gemmes::Blanc);
				break;
			case 5:
				boutton->setGemmes(Gemmes::Perle);
				break;
			case 6:
				boutton->setGemmes(Gemmes::Or);
				break;
			}
			boutton->setNb(4);
			grid->addWidget(boutton, 1, i + 1);
			gem[i] = boutton;
	}

	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
}

PlayerGemsUI::~PlayerGemsUI() {
	delete[] gem;
	QWidget::~QWidget();
}

void PlayerGemsUI::paintEvent(QPaintEvent* event) {
	//on peint la case de transparent
	QPainter painter(this);
	QPixmap pix = Image::getPlayerGems();
	for (int i = 0; i < 7; i++) {
		painter.drawPixmap(width() /7*i, 0, width()/7, height(), pix);
	}
}


void PlayerGemsUI::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	//on force que les gemmes soit carrer ou au moins width > height/2
	int min = qMin(width() / 7, height()/3*2);
	resize(min*7, min/2*3);
	this->update();
}

void PlayerGemsUI::gemsAdd(const Gemmes& g) {
	gem[g]->setNb(gem[g]->getNb() + 1);
}

void PlayerGemsUI::gemsSupp(const Gemmes& g) {
	gem[g]->setNb(gem[g]->getNb() - 1);
}