#pragma once
#include <qwidget.h>
#include <qevent.h>
class PrivilegeUI : public QWidget
{
	Q_OBJECT
public:
	PrivilegeUI(QWidget* parent);

private:
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	bool hover;
	bool havePrivilege;
};

