#pragma once

#include <qwidget.h>
#include "Board.h"
#include "BoardUI.h"
#include "RemplirBoardUI.h"

/// <summary>
/// class de tout notre board (plateau + remplir)
/// ainsi que les Cartes
/// </summary>
class CompleteBoardUI : public QWidget
{
	Q_OBJECT

public:

	CompleteBoardUI(QWidget* parent, Board b);
	inline ~CompleteBoardUI();

	//redistribue l'event au bon composant
	inline void changeDirection(){ board.changeDirection(); };
	//redistribue l'event au bon composant
	inline void changeNbGemmesTOSelect() { board.changeNbGemmes(); };
	//redistribue l'event de rmeplir le board
	inline void remplirBoard(Board b) { board.setGemmes(b); };
private:
	BoardUI board;
	RemplirBoard remplir;

	void resizeEvent(QResizeEvent* event);
};



