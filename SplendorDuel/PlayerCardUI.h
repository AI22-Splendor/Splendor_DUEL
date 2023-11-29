#pragma once
#include "CardContainersGUI.h"
#include "CardUI.h"
#include "Card.h"
class PlayerCardUI : public CardContainersGUI
{
		Q_OBJECT
	public:
		PlayerCardUI(QWidget* parent);
		~PlayerCardUI();

		/// <summary>
		/// Ajoute la carte dans la main du joeur
		/// </summary>
		/// <param name="g">la carte</param>
		void addCarte(const Card* c);

private:
	void clickDCard(int col, int ligne, const Card* c){}
	void clickCard(int col, int ligne, const Card* c);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	CardUI** cards;
};

