#pragma once
#include <qwidget.h>
// Ajoutez la déclaration avant (forward declaration)
#include "PlayerGemsUI.h"
#include "Gemmes.h"

/// <summary>
/// class du joeur (Gemmes + carte + points, privilège, ...)
/// </summary>
class PlayersUI : public QWidget
{
	Q_OBJECT
public:
	/// <summary>
	/// creér un menu d'un nouveau jouer
	/// </summary>
	/// <param name="parent">le widget parent</param>
	/// <param name="player">son numéro</param>
	PlayersUI(QWidget* parent, int player);
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
private:
	
	//son numéro de joeur
	int player;
	//ses gemmes
	PlayerGemsUI* pgems;
};