#pragma once

#include <qwidget.h>
#include "Board.h"
#include "BoardUI.h"
#include "RemplirBoardUI.h"
class CompleteBoardUI : public QWidget
{
	Q_OBJECT

public:

	CompleteBoardUI(QWidget* parent, Board b);

	inline ~CompleteBoardUI() { QWidget::~QWidget(); }
	inline void changeDirection(){ board.changeDirection(); };
	inline void remplirBoard(Board b) { board.setGemmes(b); };
private:
	BoardUI board;
	RemplirBoard remplir;

	
	void resizeEvent(QResizeEvent* event);
};



