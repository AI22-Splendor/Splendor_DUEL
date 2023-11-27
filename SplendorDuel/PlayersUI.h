#pragma once
#include <qwidget.h>
// Ajoutez la d�claration avant (forward declaration)
#include "PlayerGemsUI.h"
#include "PlayerCardUI.h"
#include "PlayerNameUI.h"
#include <qpainter.h>
#include "Gemmes.h"

/// <summary>
/// class du joeur (Gemmes + carte + points, privil�ge, ...)
/// </summary>
class PlayersUI : public QWidget
{
	Q_OBJECT
public:
	/// <summary>
	/// cre�r un menu d'un nouveau jouer
	/// </summary>
	/// <param name="parent">le widget parent</param>
	/// <param name="player">son num�ro</param>
	PlayersUI(QWidget* parent, QString pname, int nb);
	~PlayersUI();

	/// <summary>
	/// ajoute 1 a la gems
	/// </summary>
	/// <param name="g">la gems</param>
	inline void gemsAdd(const Gemmes& g) { pgems->gemsAdd(g); };
	/// <summary>
	/// retire 1 a la gems
	/// </summary>
	/// <param name="g">la gems</param>
	inline void gemsSupp(const Gemmes& g) { pgems->gemsSupp(g); };

	inline void changePtour(bool b) {
		name->setTour(b);
	};

private:
	void paintEvent(QPaintEvent* event) {
		QPainter(this).drawPixmap(0, 0, width(), height(), QPixmap("./res/playerFond.png"));
	}
	//son num�ro de joeur
	//ses gemmes
	PlayerGemsUI* pgems;
	PlayerCardUI* pcard;
	PlayerNameUI* name;
};