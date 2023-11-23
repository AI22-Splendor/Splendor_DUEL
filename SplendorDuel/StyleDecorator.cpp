#include "StyleDecorator.h"
#include <iostream>
void StyleDecorator::ajouter(const QString type, const QString value) {
	
	if (this->type.compare(type)==0) {
		this->value = value;
	}
	else if (this->suivant == nullptr) {
		this->suivant = new StyleDecorator(type, value);
	}
	else
	{
		this->suivant->ajouter(type, value);
	}
}

void StyleDecorator::retirer(const QString type, const QString value) {
	if (this->type == type)
		*this = *this->suivant;
	if (this->suivant != nullptr)
		this->suivant->retirer(type, value);
}

const QString StyleDecorator::text() const {
	if (this->suivant != nullptr)
		return type + ": " + value + ";" + this->suivant->text();
	return type + ": " + value + ";";
}