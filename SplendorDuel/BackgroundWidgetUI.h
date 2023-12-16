#ifndef BACKGROUNDWIDGETUI_H
#define BACKGROUNDWIDGETUI_H

#include <qwidget.h>
#include <iostream>
class BackgroundWidgetUI : public QWidget
{
public:
	BackgroundWidgetUI(QWidget* parent, QPixmap pix) : QWidget(parent), pix(pix) {}
private:
	void paintEvent(QPaintEvent* event);
	QPixmap pix;
};

#endif

