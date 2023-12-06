#pragma once

#include "Gemmes.h"
#include "MyException.h"
#include <qlist.h>
#include "Action.h"
extern const unsigned int NB_GEMMES_PAIEMENTS;

class Card {
public:
	/**
	* Le niveau de la carte doit être compris entre 1 et 3 (inclus)
	* 
	*/
	Card(const unsigned int level, const unsigned int ptsPrestige, const EnumGemmes bonus, const unsigned int nbBonus = 1,
		const unsigned int crowns = 0, const string imageSrc = "./res/blanc1.png", const QList<EnumAction> action = QList<EnumAction>{});

	/**
	* Definit le prix de la carte pour la gemme donnée
	*/
	void setCost(const EnumGemmes type, const unsigned int price);

	/// <summary>
	/// Verifie si la carte peut être achetée à partir des paramètres
	/// </summary>
	/// <param name="wallet">Le portefeuille actuel du joueur (organisé a partir de l'enum Gemmes)</param>
	/// <returns>true si la carte peut être achetée, false sinons</returns>
	bool canBeBought(const unsigned int* wallet) const;
	unsigned int getPriceForGemme(EnumGemmes gem) const { return cost[gem];  };
	
	unsigned int getLevel() const { return level;  }
	unsigned int getPointsPrestige() const { return ptsPrestige;  }
	EnumGemmes getDiscountType() const { return discountType;  }
	unsigned int getDiscount() const { return discount;  }
	unsigned int getCrowns() const { return crowns;  }
	inline void setDiscountType(const EnumGemmes g) { discountType = g; }
	inline const QList<EnumAction> getEffect() const { return effects; };
	QString getImageSrc() const { return imageSrc; }

	inline bool operator==(const Card& card) { 
		if (effects.size() != card.effects.size()) return false;
		for (int i = 0; i < effects.size(); i++) {
			if (effects[i] != card.effects[i]) return false;
		}
		for (int i = 0; i < NB_GEMMES_PAIEMENTS; i++) {
			if (cost[i] != card.cost[i]) return false;
		}
		return card.discountType == discountType
			&& card.discount == discount
			&& card.crowns == crowns
			&& card.ptsPrestige == ptsPrestige
			&& card.level == level
			&& card.imageSrc.compare(imageSrc) == 0;
	}

private:
	unsigned int cost[NB_GEMMES_PAIEMENTS];
	unsigned int level;
	unsigned int ptsPrestige;
	// Si le bonus est de type Gemmes::Vide, alors c'est un bonus pour tous les types de Gemmes
	EnumGemmes discountType;
	unsigned int discount;
	unsigned int crowns;
	QString imageSrc;
	QList<EnumAction> effects;
	friend ostream& operator<<(ostream& os, const Card card);
};

ostream& operator<<(ostream& os, const Card card);