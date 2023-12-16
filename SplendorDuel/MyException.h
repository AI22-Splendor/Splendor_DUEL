#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
#include <string>

//Class pour creer mes Exception
//elle contiendra juste un string donne a la construction
using namespace std;
class MyException
{
public:
	//Constructeur
	inline MyException(const char* c) {
		this->erreur = c;
	};

	//getteur de l'erreur
    string inline getErreur() { return this->erreur; }

	//operateur<< pour l'afficher facilement
    inline ostream& operator<<(ostream& left) {
		left << this->erreur;
		return left;
	}

private:
    string erreur;
};

#endif