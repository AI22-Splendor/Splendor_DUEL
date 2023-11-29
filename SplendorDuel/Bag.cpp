#include "Bag.h"
#include "MyException.h"

#include <ctime>
#include <iostream>
using namespace std;


//Constructeur
//param : la taille du sac
Bag::Bag(const int n)
{
	this->bag = new Gemmes[n];
	this->taille = n;
	for (int i = 0; i < n; i++)
	{
		this->bag[i] = Gemmes::Vide;
	}
}

//connaitre le nombre de Gemmes dans le sac
//return : le nombre de Gemmes
int Bag::getNbGemmes() const{
	int n = 0;
	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] != Gemmes::Vide) n++;
	}
	return n;
}

//Ajouter une Gemme dans le sac
//Param : Gemmes g : la couleur de la Gemmes
//Param : int nbGemmes : nombre de gemmes a ajouter
//return void
//throw Exception si le sac est deja rempli
void Bag::addGemmes(const Gemmes g, int nbGemmes) {
	cout << "Nb Gemmes actu: " << this->getNbGemmes() << " a ajouter: " << nbGemmes << " taillemax: " << this->taille << endl;
	if ((this->getNbGemmes() + nbGemmes) > this->taille) {
		//On creer notre Exception:
		MyException exep("Erreur dans l'ajout des gemmes, le sac ne peut pas accepter autant de gemmes");
		throw exep;
	}

		//on cherche une place vide
	for (int i = 0; i < this->getTaille() && nbGemmes > 0; i++) {
			//si vide
		if (this->bag[i] == Gemmes::Vide) {
			//on ajoute
			this->bag[i] = g;
			nbGemmes--;
		}
	}
}

//Retire une Gemme du Sac
//Prerequis : le Sac dois en contenir une de ce type
//param : g - le Type de Gemmes a supprimer
//param : nbGemmes - le nombre de gemmes a supprimer
//throw Exception si on la possede pas
void Bag::suppGemmes(const Gemmes g, unsigned int nbGemmes) {
	//on cherche la gemme

	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] == g) {
			this->bag[i] = Gemmes::Vide;
			nbGemmes--;
			if (nbGemmes == 0) return;
		}
	}

	//On creer notre Exception:
	//car le sac ne contenais pas cette Gemme
	MyException exep("Pas assez de gemmes dans le bag pour en supprimer autant");
	throw exep;
}


//Avoir le nombre de Gemme de la couleur donne
//param : la couleur
//return le nombre
int Bag::getNbGemmesType(const Gemmes &g) const {
	int n = 0;
	for (int i = 0; i < this->getTaille(); i++) {
		if (this->bag[i] == g)
			n++;
	}
	return n;
}

//Melanger les Gemmes dans le sac
void Bag::melanger() const {
    srand(time(nullptr));
	for (int i = 0; i < this->getTaille(); i++) {
        int nb = rand() % this->getTaille();
		if (nb != i) {
			Gemmes cpy = this->bag[i];
			this->bag[i] = this->bag[nb];
			this->bag[nb] = cpy;
		}
	}
}

/**
* Mélange puis renvoie une gemme présente dans le bag 
*/
Gemmes Bag::piocherGemme() const {
	this->melanger();
	if (this->getNbGemmes() <= 0) {
		return Gemmes::Vide;
	}
	for (int i = 0; i < this->getTaille(); i++) {
		if (bag[i] != Gemmes::Vide) {
			Gemmes pioche = bag[i];
			bag[i] = Gemmes::Vide;
			return pioche;
		}
	}
	return Gemmes::Vide;
}