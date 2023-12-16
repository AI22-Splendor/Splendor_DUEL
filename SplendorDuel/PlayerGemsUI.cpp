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
				boutton->setGemmes(EnumGemmes::Vert);
				break;
			case 1:
				boutton->setGemmes(EnumGemmes::Rouge);
				break;
			case 2:
				boutton->setGemmes(EnumGemmes::Bleu);
				break;
			case 3:
				boutton->setGemmes(EnumGemmes::Noir);
				break;
			case 4:
				boutton->setGemmes(EnumGemmes::Blanc);
				break;
			case 5:
				boutton->setGemmes(EnumGemmes::Perle);
				break;
			case 6:
				boutton->setGemmes(EnumGemmes::Or);
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

void PlayerGemsUI::setGems(const EnumGemmes g, const int nb) {
	this->gem[g]->setNb(nb);
}

<<<<<<< HEAD
<<<<<<< Updated upstream
void PlayerGemsUI::clickGemmes(Gemmes g) {
		if (GameHandler::getInstance().suppPlayerGems(g, pnum)) {
=======
bool PlayerGemsUI::clickGemmes(EnumGemmes g) {
		if (SingletonGameHandler::getInstance().suppPlayerGems(g, pnum)) {
>>>>>>> Stashed changes
=======
void PlayerGemsUI::clickGemmes(EnumGemmes g) {
		if (SingletonGameHandler::getInstance().suppPlayerGems(g, pnum)) {
>>>>>>> 837c85eb72fd14b5c5985edc33ba1f6b11654a39
			SplendorDuel::changePtour();
			SplendorDuel::refreshPlayersGems(0);
			SplendorDuel::refreshPlayersGems(1);
			SplendorDuel::refreshMessage();
		}
		else {
			if (selected != -1) {
				gem[selected]->showErr();
			}
		}
		return true;
	}

void PlayerGemsUI::hoverGemmes(const int pos, const bool red) {
	this->gem[pos]->hover(red);
	selected = pos;
};