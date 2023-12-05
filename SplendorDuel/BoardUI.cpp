#include "BoardUI.h"
#include "SplendorDuel.h"
#include "GemmesUI.h"
#include "Board.h"
#include "GameHandler.h"
#include <qpixmap.h>
#include <qgridlayout.h>
#include "Image.h"

BoardUI::BoardUI(QWidget* parent): GemmesContainerGUI(parent), nbGemmes(3){
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
	int nb = SingletonGameHandler::getInstance().getInstance().gemmesToSelect();
	//la gemme centrale
	posSelect[0] = pos;
	if (nb>1 && this->nbGemmes>1) {
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
		if ((pos % 5) != 0 && tabCase[pos/5][pos%5-1]->getGemmes()!=EnumGemmes::Vide) {
			posSelect[1] = pos - 1;
		}else {
			posSelect[1] = -1;
		}
		//si pas tout a droite
		if ((pos % 5) < Board::BOARD_SIDE - 1 && tabCase[pos / 5][pos % 5 +1]->getGemmes() != EnumGemmes::Vide) {
			if (nbGemmes > 2 || posSelect[1] == -1)
				posSelect[2] = pos + 1;
		}else {
			posSelect[2] = -1;
		}
		break;
	case BoardUI::VERTICALE:
		//si pas tout en haut
		if ((pos / 5) != 0 && tabCase[pos / 5 -1][pos % 5]->getGemmes() != EnumGemmes::Vide) {
			posSelect[1] = pos - 5;
		}
		else {
			posSelect[1] = -1;
		}
		//si pas tout en bas
		if ((pos / 5) < Board::BOARD_SIDE - 1 && tabCase[pos / 5 +1][pos % 5]->getGemmes() != EnumGemmes::Vide) {
			if (nbGemmes > 2 || posSelect[1] == -1)
				posSelect[2] = pos + 5;
		}
		else {
			posSelect[2] = -1;
		}
		break;
	case BoardUI::DIAGONALED:
		//si pas tout a gauche et en bas
		if ((pos % 5) != 0 && (pos / 5) < Board::BOARD_SIDE-1 && tabCase[pos / 5+1][pos % 5-1]->getGemmes() != EnumGemmes::Vide) {
			posSelect[1] = pos - 1 + 5;
		}
		else {
			posSelect[1] = -1;
		}
		//si pas tout a droite et en haut
		if ((pos % 5) < Board::BOARD_SIDE - 1 && (pos/5) > 0 && tabCase[pos / 5-1][pos % 5+1]->getGemmes() != EnumGemmes::Vide) {
			if (nbGemmes > 2 || posSelect[1] == -1)
				posSelect[2] = pos + 1 - 5;
		}
		else {
			posSelect[2] = -1;
		}
		break;
	case BoardUI::DIAGONALEL:
		//si pas tout a gauvhe et en haut
		if ((pos % 5) != 0 && (pos / 5) > 0 && tabCase[pos / 5-1][pos % 5-1]->getGemmes() != EnumGemmes::Vide) {
			posSelect[1] = pos - 1 - 5;
		}
		else {
			posSelect[1] = -1;
		}
		//si pas tout a droite et en bas
		if ((pos % 5) < Board::BOARD_SIDE - 1 && (pos / 5) < Board::BOARD_SIDE - 1 && tabCase[pos / 5+1][pos % 5+1]->getGemmes() != EnumGemmes::Vide) {
			if (nbGemmes > 2 || posSelect[1] == -1)
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
		if (i > 0)
			posSelect[i] = -1;
	}
	if (posSelect[0] != -1)
		this->hoverGemmes(posSelect[0], true);
}

void BoardUI::changeNbGemmes() {
	this->nbGemmes++;
	if (this->nbGemmes == 4)
		this->nbGemmes = 1;
	//on remet les cases en noir
	for (int i = 0; i < 3; i++) {
		if (posSelect[i] != -1)
		{
			tabCase[posSelect[i] / 5][posSelect[i] % 5]->hover(false);
		}
	}
	if (posSelect[0] != -1)
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

void BoardUI::clickGemmes(EnumGemmes g) {
	int pturn;
	if (SingletonGameHandler::getInstance().getInstance().isPlayer1Turn())
		pturn = 0;
	else {
		pturn = 1;
	}
	//si les règles sont ok
	if (SingletonGameHandler::getInstance().getInstance().gemmesPick(posSelect)) {
		for (int i = 0; i < 3; i++) {
			if (posSelect[i] != -1) {
				SplendorDuel::refreshPlayersGems(pturn);
				tabCase[posSelect[i] / 5][posSelect[i] % 5]->setGemmes(EnumGemmes::Vide);
				tabCase[posSelect[i] / 5][posSelect[i] % 5]->hover(false);
				posSelect[i] = -1;
			}
		}
		SplendorDuel::changePtour();
		SplendorDuel::refreshPrivilege();
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (posSelect[i] != -1) {
				tabCase[posSelect[i] / 5][posSelect[i] % 5]->showErr();
			}
		}
	}
}