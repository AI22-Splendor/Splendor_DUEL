#ifndef BOARDCARD_H
#define BOARDCARD_H

#include "GemmesContainerGUI.h"
#include "CardUI.h"
#include "Card.h"
class BoardCardUI : public CardContainersGUI
{
	Q_OBJECT
public:
	BoardCardUI(QWidget* parent);
	~BoardCardUI();

	/// <summary>
	/// Ajoute la carte dans la main du joeur
	/// </summary>
	/// <param name="g">la carte</param>
	void addCarte(const EnumGemmes& g, Card c) {}

	/// <summary>
	/// suppprime la card de la main du joueur
	/// </summary>
	/// <param name="g">la carte param>
	void suppCarte(const EnumGemmes& g, Card c) {}

private:
	void clickDCard(int col, int ligne, Card* c);
	void clickCard(int col, int ligne, Card* c);
	CardUI*** cards;
	friend class AI;
};

#endif