#include "Image.h"


Image* Image::instance = nullptr;

Image::Image() {
	blanc = QPixmap("./res/blanc.png");
	noir = QPixmap("./res/noir.png");
	vert = QPixmap("./res/vert.png");
	rouge = QPixmap("./res/rouge.png");
	perle = QPixmap("./res/perle.png");
	gold = QPixmap("./res/or.png");
	bleu = QPixmap("./res/bleu.png");
	plateau = QPixmap("./res/plateau.png");
	underPlat = QPixmap("./res/actions.png");
	remplir = QPixmap("./res/remplir.png");
	playerGems = QPixmap("./res/playergemmes.png");
	cartvide = QPixmap("./res/0.png");
	ppoints= QPixmap("./res/points.png");
	fond= QPixmap("./res/fond.png");
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

QPixmap Image::getPlayerGems() {
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->playerGems;
}

QPixmap Image::getCarteVide() {
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->cartvide;
}

QPixmap Image::getPlayersPoints() {
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->ppoints;
}

QPixmap Image::getFond() {
	if (instance == nullptr) {
		instance = new Image();
	}
	return instance->fond;
}

QPixmap& Image::getImageFromSrc(const QString src) {
	return *(new QPixmap(src));
}