#pragma once

#include "Gemmes.h"
#include "MyException.h"

extern const unsigned int NB_GEMMES_PAIEMENTS;

class Card {
public:
	/**
	* Le niveau de la carte doit être compris entre 1 et 3 (inclus)
	* 
	*/
	Card(const unsigned int level, const unsigned int ptsPrestige, const Gemmes bonus, const unsigned int nbBonus = 1, const unsigned int crowns = 0);

	/**
	* Definit le prix de la carte pour la gemme donnée
	*/
	void setCost(const Gemmes type, const unsigned int price);

	/// <summary>
	/// Verifie si la carte peut être achetée à partir des paramètres
	/// </summary>
	/// <param name="wallet">Le portefeuille actuel du joueur (organisé a partir de l'enum Gemmes)</param>
	/// <returns>true si la carte peut être achetée, false sinons</returns>
	bool canBeBought(const int* wallet) const;
	
	unsigned int getPointsPrestige() const { return ptsPrestige;  }
	Gemmes getBonusType() const { return bonusType;  }
	unsigned int getBonusNombre() const { return nbBonus;  }
	unsigned int getCrowns() const { return crowns;  }

private:
	int* cost;
	unsigned int level;
	unsigned int ptsPrestige;
	// Si le bonus est de type Gemmes::Vide, alors c'est un bonus pour tous les types de Gemmes
	Gemmes bonusType;
	unsigned int nbBonus;
	unsigned int crowns;
};

