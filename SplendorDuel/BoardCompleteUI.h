#pragma once
#include "GemmesUI.h"
#include <qwidget.h>
#include "Gemmes.h"
#include "GemmesContainerGUI.h"

class BoardComplete : public QWidget
{
	Q_OBJECT

public:

	BoardComplete(QWidget* parent);

	inline ~BoardComplete() { QWidget::~QWidget(); }

private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);

	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
};

