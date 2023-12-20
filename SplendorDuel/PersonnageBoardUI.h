#ifndef PERSONNAGEBOARDUI_H
#define PERSONNAGEBOARDUI_H

#include "CardContainersGUI.h"
#include "CardUI.h"
#include "Card.h"
#include "Image.h"
#include <qpainter.h>
#include "GameHandler.h"
class PersonnageBoardUI : public CardContainersGUI
{
	Q_OBJECT
public:
	PersonnageBoardUI(QWidget* parent);
	~PersonnageBoardUI();

	/// <summary>
	/// suppprime la card de la main du joueur
	/// </summary>
	/// <param name="g">la carte param>
	void suppCarte(const EnumGemmes& g, Card c) {}

private:
	void clickDCard(int col, int ligne, Card* c) {}
	void clickCard(int col, int ligne, Card* c);
	CardUI** cards;
	friend class AI;
};

#endif