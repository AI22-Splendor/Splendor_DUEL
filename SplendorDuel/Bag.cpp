#include "Bag.h"
#include <ctime>
#include <cstdlib>
#include "MyException.h"

//Constructeur
//param : la taille du sac
Bag::Bag(const int &n)
{
	this->bag = new Gemmes[n];
	for (int i = 0; i < n; i++)
	{
		this->bag[i] = Gemmes::Vide;
	}
	this->taille = n;
}

//connaitre le nombre de gemmes dans le sac
//return : le nombre de Gemmes
int Bag::getNbGemmes() {
	int n = 0;
	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] != Gemmes::Vide) n++;
	}
	return n;
}

//Ajouter une Gemme dans le sac
//Param : Gemmes g : la couleur de la Gemmes
//return void
//throw Exception si le sac est deja rempli
void Bag::addGemmes(const Gemmes &g) {
	if (this->getNbGemmes() == this->taille) {
		//On creer notre Exception:
		MyException exep("Erreur dans l'ajout d'une gemme, sac dej� rempli");
		throw exep;
	}

	//on l'initialise vide
	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] == Gemmes::Vide) {
			this->bag[i] = g;
			return;
		}
	}
}

//Retire une Gemme du Sac
//Prerequis : le Sac dois en contenir une de ce type
//param : le Type de Gemmes a supprimer
//throw Exception si on la possede pas
void Bag::suppGemmes(const Gemmes &g) {
	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] == g) {
			this->bag[i] = Gemmes::Vide;
			return;
		}
	}

	//On creer notre Exception:
	//car le sac ne contenais pas cette Gemme
	MyException exep("Erreur dans la suppresion d'une gemme, gemme manquante");
	throw exep;
}


//Avoir le nombre de Gemme de la couleur donne
//param : la couleur
//return le nombre
int Bag::getNbGemmesType(const Gemmes &g) {
	int n = 0;
	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] == g)
			n++;
	}
	return n;
}

//Melanger les Gemmes dans le sac
void Bag::melanger() {
	std::srand(std::time(nullptr));
	for (int i = 0; i < this->getTaille(); i++) {
		int nb = std::rand() % this->getTaille();
		if (nb != i) {
			Gemmes cpy = this->bag[i];
			this->bag[i] = this->bag[nb];
			this->bag[nb] = cpy;
		}
	}
}
