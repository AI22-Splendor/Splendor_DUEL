#pragma once

#include <qwidget.h>
class GemmesContainerGUI : public QWidget
{
public:
	GemmesContainerGUI(QWidget* parent) : QWidget(parent) {}
	virtual void hoverGemmes(const int pos, const bool red) = 0;
	virtual void clickGemmes() = 0;
};