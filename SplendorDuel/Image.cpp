#include "Image.h"


Image* Image::instance = nullptr;

Image::Image() {
	blanc = QPixmap("./blanc.png");
	noir = QPixmap("./noir.png");
	vert = QPixmap("./vert.png");
	rouge = QPixmap("./rouge.png");
	perle = QPixmap("./perle.png");
	gold = QPixmap("./or.png");
	bleu = QPixmap("./bleu.png");
	plateau = QPixmap("./plateau.png");
	underPlat = QPixmap("./actions.png");
	remplir = QPixmap("./remplir.png");
}

void Image::destroy(){
	if(instance!=nullptr)
		delete instance;
	instance = nullptr;
}
Image::~Image() {
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}

QPixmap Image::getPixmap(const Gemmes g) {
	if (instance == nullptr) {
		instance = new Image();
	}

	switch (g)
	{
	case Gemmes::Blanc:
		return instance->blanc;
		break;
	case Gemmes::Noir:
		return instance->noir;
		break;
	case Gemmes::Rouge:
		return instance->rouge;
		break;
	case Gemmes::Or:
		return instance->gold;
		break;
	case Gemmes::Vert:
		return instance->vert;
		break;
	case Gemmes::Bleu:
		return instance->bleu;
		break;
	case Gemmes::Perle:
		return instance->perle;
		break;
	}
}

QPixmap Image::getPlateau() {
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->plateau;
}

QPixmap Image::getUnderPlateau(){
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->underPlat;
}

QPixmap Image::getRemplir() {
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->remplir;
}