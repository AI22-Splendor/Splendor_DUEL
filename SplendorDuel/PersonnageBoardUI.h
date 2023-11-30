#pragma once
#include "CardContainersGUI.h"
#include "CardUI.h"
#include "Card.h"
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
	void suppCarte(const Gemmes& g, Card c) {}

private:
	void clickDCard(int col, int ligne, Card* c) {}
	void clickCard(int col, int ligne, Card* c) {}
	void paintEvent(QPaintEvent* event) {}
	void resizeEvent(QResizeEvent* event) {}
	CardUI** cards;
};

