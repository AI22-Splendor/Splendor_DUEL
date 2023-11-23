#pragma once

#include <qwidget.h>
#include <QVBoxLayout>
#include "Board.h"
#include "qpainter.h"

#include "GemmesUI.h"
#include <vector>
class BoardUI : public QWidget
{
	Q_OBJECT

public:
	BoardUI(QWidget* parent);
	~BoardUI();
	void setGemmes(const Board& b);
	void hover(const int pos, const bool truple, const bool red);
	void changeDirection();
	const inline int getSelectedGemmes(int num)const { return posSelect[num]; }
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void selectOtherGemmes(const int pos);
	//tableau à deux dimensions
	GemmesUI*** tabCase;

	enum direction {
		HORIZONTAL = 0,
		VERTICALE = 1,
		DIAGONALED = 2,
		DIAGONALEL = 3
	};
	direction direction;
	int posSelect[3];
};

