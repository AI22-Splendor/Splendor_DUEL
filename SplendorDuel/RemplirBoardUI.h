#pragma once
#include "GemmesUI.h"
#include <qwidget.h>
#include "Gemmes.h"
#include "GemmesContainerGUI.h"

class RemplirBoard : public QWidget
{
	Q_OBJECT

public:

	RemplirBoard(QWidget* parent);
	inline ~RemplirBoard() { QWidget::~QWidget(); }

private:
	
	bool hover;
	void mouseMoveEvent(QMouseEvent* mouse);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void mousePressEvent(QMouseEvent* mouse);
	void leaveEvent(QEvent* event);
};

