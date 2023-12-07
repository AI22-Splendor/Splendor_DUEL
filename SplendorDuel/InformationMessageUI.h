#pragma once
#include <qwidget.h>
#include "Message.h"
#include <iostream>
class InformationMessageUI : public QWidget
{
public:
	InformationMessageUI(QWidget* parent);
	inline void setMessage(Message m) { message = m; update();};
private:
	void paintEvent(QPaintEvent* event);
	Message message;
};

