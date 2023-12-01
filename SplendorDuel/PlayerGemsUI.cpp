#include "PlayerGemsUI.h"
#include <qpainter.h>
#include <qpixmap.h>
#include "GameHandler.h"
#include "Image.h"
#include <qgridlayout.h>
#include "SplendorDuel.h"

PlayerGemsUI::PlayerGemsUI(QWidget* parent, int pnum) : GemmesContainerGUI(parent), pnum(pnum), selected(-1){
	this->gem =new GemmesUI*[7]();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20*7, 20);
	QGridLayout* grid = new QGridLayout(this);
	this->setLayout(grid);
	for (int i = 0; i < 7; i++) {
			GemmesUI* boutton = new GemmesUI(0, i, this);
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

void PlayerGemsUI::bigError() {
	for (int i = 0; i < NB_GEMMES_PAS_VIDE; i++) {
		this->gem[i]->showErr();
	}
}

void PlayerGemsUI::setGems(const Gemmes g, const int nb) {
	this->gem[g]->setNb(nb);
}

void PlayerGemsUI::clickGemmes(Gemmes g) {
		if (GameHandler::suppPlayerGems(g)) {
			SplendorDuel::changePtour();
			SplendorDuel::refreshPlayersGems(0);
			SplendorDuel::refreshPlayersGems(1);
		}
		else {
			if (selected != -1) {
				gem[selected]->showErr();
			}
		}
	}

void PlayerGemsUI::hoverGemmes(const int pos, const bool red) {
	this->gem[pos]->hover(red);
	selected = pos;
};