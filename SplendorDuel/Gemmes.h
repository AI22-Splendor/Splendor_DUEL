#ifndef GEMMES_H
#define GEMMES_H

#include <iostream>

using namespace std;

//Class enum pouvant representer toutes les couleurs des gemmes
//ainsi que Vide = rien
enum Gemmes
{
	Vert,
	Rouge,
	Bleu,
	Noir,
	Blanc,
	Or,
	Perle,
	Vide
};


ostream& operator<<(ostream& os, const Gemmes& gem);

#endif