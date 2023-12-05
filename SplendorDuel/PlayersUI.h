#pragma once
#include <qwidget.h>
// Ajoutez la déclaration avant (forward declaration)
#include "PlayerGemsUI.h"
#include "PlayerCardUI.h"
#include "PlayerNameUI.h"
#include <qpainter.h>
#include "PlayerPoints.h"
#include "Player.h"
#include "Gemmes.h"
#include "BackgroundWidgetUI.h"

/// <summary>
/// class du joeur (Gemmes + carte + points, privilège, ...)
/// </summary>
class PlayersUI : public BackgroundWidgetUI
{
	Q_OBJECT
public:
	/// <summary>
	/// creér un menu d'un nouveau jouer
	/// </summary>
	/// <param name="parent">le widget parent</param>
	/// <param name="player">son numéro</param>
	PlayersUI(QWidget* parent, Player* p, int nb);
	~PlayersUI();


	/// refresh les gemmes du joueurs
	/// </summary>
	void setGemmes();

	/// <summary>
	/// retire 1 a la gems
	/// </summary>
	/// <param name="g">la gems</param>
	void ajouterCarte(Card* c);

	inline void changePtour(bool b) {
		name->setTour(b);
	};

	inline void addCouronne(const int nb) { points->updateCouronne(nb); }
	inline void addPrestiges(const int nb) { points->udpdatePrestiges(nb); }
	inline void setPoints(const EnumGemmes g) { 
		if (p->getPrestige(g) > points->getPoints() && g!=EnumGemmes::Vide)
			points->updatePoints(p->getPrestige(g));
	}

	inline void reservCard(Card* c) { this->points->updateCard(c); };

private:
	//son numéro de joeur
	//ses gemmes
	Player* p;
	PlayerGemsUI* pgems;
	PlayerCardUI* pcard;
	PlayerNameUI* name;
	PlayerPoints* points;
};