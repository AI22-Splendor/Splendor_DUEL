#pragma once
#include "GemmesContainerGUI.h"
#include "GemmesUI.h"
class PlayerGemsUI : public GemmesContainerGUI
{
	Q_OBJECT
public:
	PlayerGemsUI(QWidget* parent);
	~PlayerGemsUI();
	void gemsAdd(const Gemmes& g);
	void gemsSupp(const Gemmes& g);
private:
	void hoverGemmes(const int pos, const bool red) {};
	void clickGemmes() { /*TODO*/ };
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	GemmesUI** gem;
};

