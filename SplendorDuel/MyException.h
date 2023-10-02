#pragma once
#include <string>
#include <iostream>

//Class pour créer mes Exception
//elle contiendra juste un string donné a la construction
class MyException
{
public:
	//Constructeur
	inline MyException(const char* c) {
		this->erreur = c;
	};

	//getteur de l'erreur
	std::string inline getErreur() { return this->erreur; }

	//operateur<< pour l'afficher facilement
	inline std::ostream& operator<<(std::ostream& left) {
		left << this->erreur;
		return left;
	}

private:
	std::string erreur;
};


