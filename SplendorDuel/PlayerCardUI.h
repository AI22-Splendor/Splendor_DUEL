#pragma once
#include "GemmesContainerGUI.h"
#include "CardUI.h"
#include "Card.h"
class PlayerCardUI : public GemmesContainerGUI
{
		Q_OBJECT
	public:
		PlayerCardUI(QWidget* parent);
		~PlayerCardUI();

		/// <summary>
		/// Ajoute la carte dans la main du joeur
		/// </summary>
		/// <param name="g">la carte</param>
		void addCarte(const Gemmes& g, Card c){}

		/// <summary>
		/// suppprime la card de la main du joueur
		/// </summary>
		/// <param name="g">la carte param>
		void suppCarte(const Gemmes& g, Card c){}

private:
	void hoverGemmes(const int pos, const bool red) {};
	void clickGemmes(Gemmes g) { /*TODO*/ };
	void clickCard() { /*TODO*/ }
	void paintEvent(QPaintEvent* event){}
	void resizeEvent(QResizeEvent* event){}
	CardUI** cards;
};

