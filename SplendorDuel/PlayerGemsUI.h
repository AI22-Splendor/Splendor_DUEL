#pragma once
#include "GemmesContainerGUI.h"
#include "GemmesUI.h"

/// <summary>
/// Le tableau des gemmes du joueurs
/// c'est un GemmesContainerGUI
/// </summary>
class PlayerGemsUI : public GemmesContainerGUI
{
	Q_OBJECT
public:
	PlayerGemsUI(QWidget* parent, int pnum);
	~PlayerGemsUI();
	void bigError();
	void setGems(const EnumGemmes g, const int nb);

private:
	void clickCard() {};
	void hoverGemmes(const int pos, const bool red);
	void clickGemmes(EnumGemmes g);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	GemmesUI** gem;
	const int pnum;
	int selected;
};

