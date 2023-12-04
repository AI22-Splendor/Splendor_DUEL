#pragma once
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

	PrivilegeUI*** tab;
};

