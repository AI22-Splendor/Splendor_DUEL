#ifndef REMPLIRBOARDUI_H
#define REMPLIRBOARDUI_H

#include "GemmesUI.h"
#include <qwidget.h>
#include "Gemmes.h"
#include "GemmesContainerGUI.h"

class RemplirBoardUI : public QWidget
{
	Q_OBJECT

public:

	RemplirBoardUI(QWidget* parent);
	inline ~RemplirBoardUI() { QWidget::~QWidget(); }

private:
	friend class AI;
	bool hover;
	void mouseMoveEvent(QMouseEvent* mouse);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void mousePressEvent(QMouseEvent* mouse);
	void leaveEvent(QEvent* event);

	friend class AI;
};

#endif