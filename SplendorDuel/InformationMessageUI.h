#ifndef INFORMATIONMESSAGEUI_H
#define INFORMATIONMESSAGEUI_H

#include <qwidget.h>
#include <qpushbutton.h>
#include "Message.h"
#include <iostream>
#include <qtimer.h>
class InformationMessageUI : public QWidget
{
	Q_OBJECT
public:
	InformationMessageUI(QWidget* parent);
	void setMessage(Message m);
	void timerEvent(QTimerEvent* event);
private:
	void paintEvent(QPaintEvent* event);
	Message message;
	bool afficher;
	bool err;
	QPushButton button;

private slots:
	void showInformation();
};

#endif