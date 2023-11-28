#pragma once
#include <qwidget.h>

class PlayerPoints : public QWidget
{
	Q_OBJECT

public:
	PlayerPoints(QWidget* parent);
	~PlayerPoints();
private:
	void paintEvent(QPaintEvent* event);
};

