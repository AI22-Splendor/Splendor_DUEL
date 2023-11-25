#include "BoardUI.h"
#include "SplendorDuel.h"
#include "GemmesUI.h"
#include "Board.h"
#include "GameHandler.h"
#include <qpixmap.h>
#include <qgridlayout.h>
#include "Image.h"

BoardUI::BoardUI(QWidget* parent): GemmesContainerGUI(parent){
	for (int i = 0; i < 3; i++) {
		//valeur sentinelle : aucune gemmes select
		posSelect[i] = -1;
	}
	//direction de base
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
			grid->addWidget(boutton, i+1, j+1);
			tabCase[i][j] = boutton;
		}
	}

	grid->setContentsMargins(0, 0, 0, 0);
	grid->setSpacing(0);
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

void BoardUI::hoverGemmes(const int pos, const bool red){
	//on demande au GH le nombre de gemmes a selectionner
	int nb = GameHandler::gemmesToSelect();
	//la gemme centrale
	posSelect[0] = pos;
	if (nb==3) {
		//on ajoute au tableau les 2 autres gemmes si posible en fonction de la direction
		selectOtherGemmes(pos);
	}
	else {
		//Si 1 seul gemmes à selectonner
		// pas besoin de calculer ses voisines
		//On selectionne que la Gemmes
		posSelect[0] = pos;
		posSelect[1] = -1;
		posSelect[2] = -1;
	}
	for (int i = 0; i < nb; i++) {
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
		this->hoverGemmes(posSelect[0], true);
}

void BoardUI::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	//on dessinne maintenant l'image du fond sur le board
	QPixmap pix = Image::getPlateau(); 
	painter.drawPixmap(0, 0, width(), height(), pix);
}

void BoardUI::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);
	//on force le carrer
	int minS = qMin(width(), height());
	resize(minS, minS);
}

void BoardUI::clickGemmes(Gemmes g) {
	if (GameHandler::gemmesToSelect() == 3) {
		bool possible = true;
		for (int i = 0; i < 3; i++) {
			if (posSelect[i] == -1)
				possible = false;
		}
		//si on a bien 3 gemmes et que les règles sont ok
		if (possible && GameHandler::gemmesPick(posSelect)) {
			for (int i = 0; i < 3; i++) {
				((SplendorDuel*)this->topLevelWidget())->addPlayerGems(tabCase[posSelect[i] / 5][posSelect[i] % 5]->getGemmes(), GameHandler::getPlayerTurn());
				tabCase[posSelect[i] / 5][posSelect[i] % 5]->setGemmes(Gemmes::Vide);
				tabCase[posSelect[i] / 5][posSelect[i] % 5]->hover(false);
				posSelect[i] = -1;
			}
		}
	}
	else {
		//TODO 1 GEMMES
	}
}