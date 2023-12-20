#ifndef PLAYERCARDUI_H
#define PLAYERCARDUI_H

#include "CardContainersGUI.h"
#include "CardUI.h"
#include "Card.h"
class PlayerCardUI : public CardContainersGUI
{
		Q_OBJECT
	public:
		PlayerCardUI(QWidget* parent, int pnum);
		~PlayerCardUI();

		/// <summary>
		/// Ajoute la carte dans la main du joeur
		/// </summary>
		/// <param name="g">la carte</param>
		void addCarte(Card* c);

private:
	void clickDCard(int col, int ligne, Card* c){}
	void clickCard(int col, int ligne, Card* c);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	CardUI** cards;
	int pnum;

	friend class AI;
};

#endif