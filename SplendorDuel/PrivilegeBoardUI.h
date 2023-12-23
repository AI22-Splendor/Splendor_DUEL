#ifndef PRIVILEGEBOARDUI_H
#define PRIVILEGEBOARDUI_H

#include <qwidget.h>
#include "PrivilegeUI.h"

class PrivilegeBoardUI : public QWidget
{
public:
	PrivilegeBoardUI(QWidget* parent);
	~PrivilegeBoardUI();
	void refreshPrivilege();
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	friend class AI;
	PrivilegeUI*** tab;
};

#endif

