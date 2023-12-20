#ifndef PLAYERGEMSUI_H
#define PLAYERGEMSUI_H

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
	void scroll(int nb)override {};
	void setGems(const EnumGemmes g, const int nb);

private:
	void clickDGemmes()override{}
	void hoverGemmes(const int pos, const bool red)override;
	void clickGemmes(EnumGemmes g)override;
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	GemmesUI** gem;
	const int pnum;
	int selected;

	friend class AI;
};

#endif