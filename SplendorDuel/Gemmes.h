#ifndef GEMMES_H
#define GEMMES_H

#include <iostream>
#include <qstring>

using namespace std;

//Class enum pouvant representer toutes les couleurs des gemmes
//ainsi que Vide = rien
enum EnumGemmes
{
	Vert = 0,
	Rouge = 1,
	Bleu = 2,
	Noir = 3,
	Blanc = 4,
	Perle = 5,
	// A partir de ces types, les élements ont des particularités
	// concernant leurs utilisation dans un paiement
	Or = 6,
	Vide = 7
};

// Nombre de gemmes permettant de payer un seul type de gemme (le sien)
// L'or ne permet pas de payer que de l'or donc n'est pas inclus dans de genre de gemmes
const unsigned int NB_GEMMES_PAIEMENTS = 6; 
const unsigned int NB_GEMMES_PAS_VIDE = 7; 

const QString gemmesToQstr(const EnumGemmes g);

ostream& operator<<(ostream& os, const EnumGemmes gem);

#endif