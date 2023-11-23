#include "BoardUI.h"

#include <qwidget.h>
#include <qgroupbox.h>
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include <qlabel.h>
#include "Board.h"
#include "GameHandler.h"
#include <qpixmap.h>


BoardUI::BoardUI(QWidget* parent): QWidget(parent){
	for (int i = 0; i < 3; i++) {
		//valeur sentinelle : aucune gemmes select
		posSelect[i] = -1;
	}
	this->direction = direction::HORIZONTAL;
	tabCase = new GemmesUI **[Board::BOARD_SIDE];
	for (int i = 0; i < Board::BOARD_SIDE; i++) {
		tabCase[i] = new GemmesUI *[Board::BOARD_SIDE];
	}

	QGridLayout* grid = new QGridLayout(this);
	this->setLayout(grid);
	
	for (int i = 0; i < Board::BOARD_SIDE; i++) {
		for (int j = 0; j < Board::BOARD_SIDE; j++) {
			GemmesUI* boutton = new GemmesUI(i, j, this);
			grid->addWidget(boutton, i, j);
			tabCase[i][j] = boutton;
		}
	}
	grid->setVerticalSpacing(height()/100);
	grid->setHorizontalSpacing(width()/100);
}

void BoardUI::setGemmes(const Board& b) {
	for (int i = 0; i < Board::BOARD_SIDE; i++) {
		for (int j = 0; j < Board::BOARD_SIDE; j++) {
			this->tabCase[i][j]->setGemmes(b.connaitreGemmes(i * Board::BOARD_SIDE + j));
			this->tabCase[i][j]->hover(false);
		}
	}
}

BoardUI::~BoardUI() {
	for (int i = 0; i < Board::BOARD_SIDE; i++) {
		delete[] tabCase[i];
	}
	delete[] tabCase; 
}

void BoardUI::hover(const int pos, const bool truple, const bool red){
	//la gemme centrale
	posSelect[0] = pos;
	if (truple) {
		//on ajoute au tableau les 2 autres gemmes si posible en fonction de la direction
		selectOtherGemmes(pos);
	}
	else {
		//On electionne que la Gemmes
		posSelect[0] = pos;
		posSelect[1] = -1;
		posSelect[2] = -1;
	}
	for (int i = 0; i < 3; i++) {
		if (posSelect[i] != -1) {
			tabCase[posSelect[i] / 5][posSelect[i] % 5]->hover(red);
			if (!red)
				posSelect[i] = -1;
		}
	}

}

void BoardUI::selectOtherGemmes(const int pos) {
	switch (direction)
	{
	case BoardUI::HORIZONTAL:
		//si col pas tout a gauche
		if ((pos % 5) != 0) {
			posSelect[1] = pos - 1;
		}else {
			posSelect[1] = -1;
		}
		//si pas tout a droite
		if ((pos % 5) < Board::BOARD_SIDE - 1) {
			posSelect[2] = pos + 1;
		}else {
			posSelect[2] = -1;
		}
		break;
	case BoardUI::VERTICALE:
		//si pas tout en haut
		if ((pos / 5) != 0) {
			posSelect[1] = pos - 5;
		}
		else {
			posSelect[1] = -1;
		}
		//si pas tout en bas
		if ((pos / 5) < Board::BOARD_SIDE - 1) {
			posSelect[2] = pos + 5;
		}
		else {
			posSelect[2] = -1;
		}
		break;
	case BoardUI::DIAGONALED:
		//si pas tout a gauche et en bas
		if ((pos % 5) != 0 && (pos / 5) < Board::BOARD_SIDE-1) {
			posSelect[1] = pos - 1 + 5;
		}
		else {
			posSelect[1] = -1;
		}
		//si pas tout a droite et en haut
		if ((pos % 5) < Board::BOARD_SIDE - 1 && (pos/5) > 0) {
			posSelect[2] = pos + 1 -5;
		}
		else {
			posSelect[2] = -1;
		}
		break;
	case BoardUI::DIAGONALEL:
		//si pas tout a gauvhe et en haut
		if ((pos % 5) != 0 && (pos / 5) > 0) {
			posSelect[1] = pos - 1 - 5;
		}
		else {
			posSelect[1] = -1;
		}
		//si pas tout a droite et en bas
		if ((pos % 5) < Board::BOARD_SIDE - 1 && (pos / 5) < Board::BOARD_SIDE - 1) {
			posSelect[2] = pos + 1 + 5;
		}
		else {
			posSelect[2] = -1;
		}
		break;
	default:
		break;
	}
}

void BoardUI::changeDirection(){
	if (direction == direction::DIAGONALED) {
		direction = direction::DIAGONALEL;
	}
	else if (direction == direction::DIAGONALEL) {
		direction = direction::HORIZONTAL;
	}
	else if (direction == direction::HORIZONTAL) {
		direction = direction::VERTICALE;
	}
	else if (direction == direction::VERTICALE) {
		direction = direction::DIAGONALED;
	}

	//on remet les cases en noir
	for (int i = 0; i < 3; i++) {
		if (posSelect[i] != -1)
		{
			tabCase[posSelect[i] / 5][posSelect[i] % 5]->hover(false);
		}
	}
	if (posSelect[0] != -1)
		//on reaffiche la nouvelle disposition en fonction des ancienne gemmes selectionner
		GameHandler::getInstance().gemmesHover(posSelect[0], true);
}

void BoardUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	//on dessinne maintenant l'image du fond sur le board
	QPixmap pix("./noir.jpg");
	painter.drawPixmap(10, 10, width() - 20, height() - 20, pix);
}

void BoardUI::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);

	int minS = qMin(width(), height());
	resize(minS, minS);
}