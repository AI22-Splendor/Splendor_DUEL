#pragma once
#include "GemmesContainerGUI.h"
#include "CardUI.h"
#include "Card.h"
class PersonnageBoardUI : public GemmesContainerGUI
{
	Q_OBJECT
public:
	PersonnageBoardUI(QWidget* parent);
	~PersonnageBoardUI();

	/// <summary>
	/// suppprime la card de la main du joueur
	/// </summary>
	/// <param name="g">la carte param>
	void suppCarte(const Gemmes& g, Card c) {}

private:
	void hoverGemmes(const int pos, const bool red) {};
	void clickGemmes(Gemmes g) {};
	void clickCard() { /*TODO*/ }
	void paintEvent(QPaintEvent* event) {}
	void resizeEvent(QResizeEvent* event) {}
	CardUI** cards;
};

