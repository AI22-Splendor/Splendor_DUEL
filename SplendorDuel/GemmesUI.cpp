#include "GemmesUI.h"
#include "GameHandler.h"
#include <qpainter.h>
#include <qevent.h>
#include "Image.h"

GemmesUI::GemmesUI(int ligne, int col, GemmesContainerGUI* parent):selected(false), ligne(ligne), col(col), QWidget(parent), gem(Gemmes::Vide){
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setMinimumSize(QSize(50, 50));
}

void GemmesUI::setGemmes(const Gemmes& g) {
	this->gem = g;
}

void GemmesUI::isClicked() {
	this->setGemmes(Gemmes::Vide);
}

void GemmesUI::mousePressEvent(QMouseEvent* mouse) {
	if(this->gem != Gemmes::Vide)
		((GemmesContainerGUI*)this->parentWidget())->clickGemmes();
}

void GemmesUI::enterEvent(QEnterEvent* event){
	if (this->gem != Gemmes::Vide)
		((GemmesContainerGUI*)this->parentWidget())->hoverGemmes(ligne * 5 + col, true);
}

void GemmesUI::leaveEvent(QEvent* event){
	if (this->gem != Gemmes::Vide)
		((GemmesContainerGUI*)this->parentWidget())->hoverGemmes(ligne * 5 + col, false);
}

void GemmesUI::hover(bool red) {
	if (red)
		selected = true;
	else
		selected = false;
	update();
}

void GemmesUI::paintEvent(QPaintEvent* event) {
	//on peint la case de transparent
	QPainter painter(this);
	//si la gemme est vide on ne peint pas la gemme
	if (gem == Gemmes::Vide)
		return;
	QPixmap pix= Image::getPixmap(gem);
	//on peint la gemmes
	switch (gem)
	{
	case Vert:
		painter.setPen(QPen(Qt::green, 3));
		break;
	case Rouge:
		painter.setPen(QPen(Qt::red, 3));
		break;
	case Bleu:
		painter.setPen(QPen(Qt::blue, 3));
		break;
	case Noir:
		painter.setPen(QPen(Qt::black, 3));
		break;
	case Blanc:
		painter.setPen(QPen(Qt::white, 3));
		break;
	case Perle:
		painter.setPen(QPen(QColor("#ff007f"), 3));
		break;
	case Or:
		painter.setPen(QPen(Qt::yellow, 3));
		break;
	default:
		break;
	}
	// Calculez le rayon du cercle
	int radius = qMin(width(), height()) / 2;

	if (!this->selected) {
		radius -= radius / 3; //1/3 plus petit que quand pas selectionner
	}

	// Calculez les coordonnées du coin supérieur gauche du rectangle englobant le cercle
	int x = width() / 2 - radius;
	int y = height() / 2 - radius;

	//on dessinne maintenant l'image au centre
	painter.drawPixmap(x, y, radius * 2, radius * 2, pix);
	
}

void GemmesUI::resizeEvent(QResizeEvent* event) {
	// Appelez la fonction de base pour que l'événement soit correctement traité
	QWidget::resizeEvent(event);
	// Forcer un nouveau rendu lorsque la taille change
	update();
}