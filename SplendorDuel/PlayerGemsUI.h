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

	/// <summary>
	/// Ajoute une gemmes à la Gemmes donné
	/// </summary>
	/// <param name="g">la gemme</param>
	void gemsAdd(const Gemmes& g);

	/// <summary>
	/// retire 1 a la gems
	/// </summary>
	/// <param name="g">la gems</param>
	void gemsSupp(const Gemmes& g);

private:
	void clickCard() {};
	void hoverGemmes(const int pos, const bool red);
	void clickGemmes(Gemmes g);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	GemmesUI** gem;
	const int pnum;
	int selected;
};

