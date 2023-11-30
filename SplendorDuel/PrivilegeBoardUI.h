#pragma once
#include <qwidget.h>
class PrivilegeBoardUI : public QWidget
{
public:
	PrivilegeBoardUI(QWidget* parent);
	~PrivilegeBoardUI();
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
};

