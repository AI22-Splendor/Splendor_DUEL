#pragma once
#include "GemmesContainerGUI.h"
#include "CardUI.h"
#include "Card.h"
class BoardCardUI : public GemmesContainerGUI
{
	Q_OBJECT
public:
	BoardCardUI(QWidget* parent);
	~BoardCardUI();

	/// <summary>
	/// Ajoute la carte dans la main du joeur
	/// </summary>
	/// <param name="g">la carte</param>
	void addCarte(const Gemmes& g, Card c) {}

	/// <summary>
	/// suppprime la card de la main du joueur
	/// </summary>
	/// <param name="g">la carte param>
	void suppCarte(const Gemmes& g, Card c) {}

private:
	void hoverGemmes(const int pos, const bool red) {};
	void clickGemmes(Gemmes g) { /*TODO*/ };
	void clickCard() { /*TODO*/ }
	void paintEvent(QPaintEvent* event) {}
	void resizeEvent(QResizeEvent* event) {}
	CardUI*** cards;
};

