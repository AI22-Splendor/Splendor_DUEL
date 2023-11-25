#pragma once
#include <qwidget.h>
// Ajoutez la déclaration avant (forward declaration)
#include "PlayerGemsUI.h"
#include "Gemmes.h"

class PlayersUI : public QWidget
{
	Q_OBJECT
public:
	PlayersUI(QWidget* parent, int player);
	~PlayersUI();
	void gemsClick();
	inline void gemsAdd(const Gemmes& g) { pgems->gemsAdd(g); };
	inline void gemsSupp(const Gemmes& g) { pgems->gemsSupp(g); };
private:
	
	int player;
	PlayerGemsUI* pgems;
};