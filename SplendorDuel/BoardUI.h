#pragma once
#include "GemmesContainerGUI.h"
#include <qwidget.h>
#include "qpainter.h"
#include "Board.h"
#include "GemmesUI.h"
#include "RemplirBoardUI.h"

class BoardUI: public GemmesContainerGUI
{

	Q_OBJECT

public:
	BoardUI(QWidget* parent);
	~BoardUI();
	void setGemmes(const Board& b);
	void hoverGemmes(const int pos, const bool red);
	void changeDirection();
	void clickGemmes();
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void selectOtherGemmes(const int pos);
	//tableau à deux dimensions
	GemmesUI*** tabCase;
	RemplirBoard *unboard;

	enum direction {
		HORIZONTAL = 0,
		VERTICALE = 1,
		DIAGONALED = 2,
		DIAGONALEL = 3
	};

	direction direction;
	int posSelect[3];
};

