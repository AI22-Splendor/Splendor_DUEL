#pragma once

#include "Gemmes.h"

//Class representant un sac de gemmes
//utilise par les Joueurs et le Plateau
class Bag
{
public:

	//Constructeur
	//param : la taille du sac
	Bag(const int n);

	//destructeur
	inline ~Bag() { delete this->bag; };

	//connaitre le nombre de gemmes dans le sac
	//return : le nombre de Gemmes
	int getNbGemmes() const;

	//Ajouter une Gemme dans le sac
	//Param : Gemmes g : la couleur de la Gemmes
	//Param : int nbGemmes : nombre de gemmes a ajouter
	//return void
	//throw Exception si le sac est deja rempli
	void addGemmes(const Gemmes g, unsigned int nbGemmes = 1);

	//Retire une Gemme du Sac
	//Prerequis : le Sac dois en contenir une de ce type
	//param : g - le Type de Gemmes a supprimer
	//param : nbGemmes - le nombre de gemmes a supprimer
	//throw Exception si on la possede pas
	void suppGemmes(const Gemmes g, const unsigned int nbGemmes = 1);


	//Avoir le nombre de Gemme de la couleur donne
	//param : la couleur
	//return le nombre
	int getNbGemmesType(const Gemmes& g) const;

	//Melanger les Gemmes dans le sac
	void melanger() const;

	//getteur de la taille du sac
	int inline getTaille() const { return this->taille; }

	/**
	* Mélange puis renvoie une gemme présente dans le bag
	* Si le bag est vide, renvoie une gemme vide
	*/
	Gemmes piocherGemme() const;

private:
	//la taille du sac
	int taille;

	//la tableau de gemmes
	Gemmes* bag;
};

