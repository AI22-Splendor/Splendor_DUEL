#pragma once
#include "Gemmes.h"

//Class représentant un "sac" de gemmes
//utilisé par les Joueurs et le Plateau
class Bag
{
public:

	//Constructeur
	//param : la taille du sac
	Bag(const int &n);

	//connaitre le nombre de gemmes dans le sac
	//return : le nombre de Gemmes
	int getNbGemmes();

	//Ajouter une Gemme dans le sac
	//Param : Gemmes g : la couleur de la Gemmes
	//return void
	//throw Exception si le sac est déja rempli
	void addGemmes(const Gemmes &g);

	//Retire une Gemme du Sac
	//Prerequis : le Sac dois en contenir une de ce type
	//param : le Type de Gemmes a supprimer
	//throw Exception si on la possede pas
	void suppGemmes(const Gemmes &g);


	//Avoir le nombre de Gemme de la couleur donne
	//param : la couleur
	//return le nombre
	int getNbGemmesType(const Gemmes &g);

	//Melanger les Gemmes dans le sac
	void melanger();

	//getteur de la taille du sac
	int inline getTaille() { return this->taille;  }

private:
	//la taille du sac
	int taille;

	//la tableau de gemmes
	Gemmes* bag;
};



