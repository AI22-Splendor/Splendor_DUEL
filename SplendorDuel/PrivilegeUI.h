#ifndef PRIVILEGEUI_H
#define PRIVILEGEUI_H

#include <qwidget.h>
#include <qevent.h>
class PrivilegeUI : public QWidget
{
	Q_OBJECT
public:
	PrivilegeUI(QWidget* parent, int pnum);
	void setPrivilege(bool have) { havePrivilege = have; update(); };
private:
	void mousePressEvent(QMouseEvent* event);
	void paintEvent(QPaintEvent* event);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	bool hover;
	int pnum;
	bool havePrivilege;
	friend class AI;
};

#endif
