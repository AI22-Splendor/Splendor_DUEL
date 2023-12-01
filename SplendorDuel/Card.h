#pragma once

#include "Gemmes.h"
#include "MyException.h"
#include <qlist.h>
#include "Action.h"
extern const unsigned int NB_GEMMES_PAIEMENTS;

class Card {
public:
	/**
	* Le niveau de la carte doit �tre compris entre 1 et 3 (inclus)
	* 
	*/
	Card(const unsigned int level, const unsigned int ptsPrestige, const Gemmes bonus, const unsigned int nbBonus = 1,
		const unsigned int crowns = 0, const string imageSrc = "./res/blanc1.png", const QList<Action> action = QList<Action>{});

	/**
	* Definit le prix de la carte pour la gemme donn�e
	*/
	void setCost(const Gemmes type, const unsigned int price);

	/// <summary>
	/// Verifie si la carte peut �tre achet�e � partir des param�tres
	/// </summary>
	/// <param name="wallet">Le portefeuille actuel du joueur (organis� a partir de l'enum Gemmes)</param>
	/// <returns>true si la carte peut �tre achet�e, false sinons</returns>
	bool canBeBought(const unsigned int* wallet) const;
	unsigned int getPriceForGemme(Gemmes gem) const { return cost[gem];  };
	
	unsigned int getLevel() const { return level;  }
	unsigned int getPointsPrestige() const { return ptsPrestige;  }
	Gemmes getDiscountType() const { return discountType;  }
	unsigned int getDiscount() const { return discount;  }
	unsigned int getCrowns() const { return crowns;  }
	inline void setDiscountType(const Gemmes g) { discountType = g; }
	inline const QList<Action> getEffect() const { return effect; };
	QString getImageSrc() const { return imageSrc; }

private:
	unsigned int cost[NB_GEMMES_PAIEMENTS];
	unsigned int level;
	unsigned int ptsPrestige;
	// Si le bonus est de type Gemmes::Vide, alors c'est un bonus pour tous les types de Gemmes
	Gemmes discountType;
	unsigned int discount;
	unsigned int crowns;
	QString imageSrc;
	QList<Action> effect;
	friend ostream& operator<<(ostream& os, const Card card);
};

ostream& operator<<(ostream& os, const Card card);