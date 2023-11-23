#include "GemmesUI.h"
#include <qwidget.h>
#include "BoardUI.h"
#include "GameHandler.h"
#include <qpainter.h>
#include <qpainterpath.h>
#include <qevent.h>

GemmesUI::GemmesUI(int ligne, int col, QWidget* parent):selected(false), ligne(ligne), col(col), QWidget(parent), gem(Gemmes::Vide){
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setMinimumSize(QSize(50, 50));
}

void GemmesUI::setGemmes(const Gemmes& g) {
	this->gem = g;
}

GemmesUI::~GemmesUI(){
	QWidget::~QWidget();
}

void GemmesUI::isClicked() {
	this->setGemmes(Gemmes::Vide);
}

void GemmesUI::mousePressEvent(QMouseEvent* mouse) {
	GameHandler::gemmesPick();
}

void GemmesUI::enterEvent(QEnterEvent* event){
	GameHandler::gemmesHover(ligne * 5 + col, true);
}

void GemmesUI::leaveEvent(QEvent* event){
	GameHandler::gemmesHover(ligne * 5 + col, false);
}

void GemmesUI::hover(bool red) {
	if (red)
		selected = true;
	else
		selected = false;
	update();
}

void GemmesUI::paintEvent(QPaintEvent* event) {
	//on peint la case:
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setBrush(QColor("#8B4513"));
	painter.drawRect(0, 0, width(), height());
	
	//si la gemme est vide on ne peint pas la gemme
	if (gem == Gemmes::Vide)
		return;

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
		painter.setPen(QPen(QColor("#f7dd36"), 3));
		break;
	case Or:
		painter.setPen(QPen(Qt::yellow, 3));
		break;
	case Vide:
		break;
	default:
		break;
	}
		
	// Dessinez le rond
	QPainterPath p = QPainterPath();
	p.addEllipse(0, 0, width(), height());
	painter.setClipPath(p);

	painter.setBrush(QColor("#8B4513"));
	if (this->selected) {
		painter.setBrush(painter.brush().color().darker(50));
	}
	// Calculez le rayon du cercle
	int radius = qMin(width(), height()) / 2;
	radius -= radius / 50; //1/50 consacré à la couleur autour

	// Calculez les coordonnées du coin supérieur gauche du rectangle englobant le cercle
	int x = width() / 2 - radius;
	int y = height() / 2 - radius;

	painter.drawEllipse(x, y, radius * 2, radius * 2);

	radius = radius / 3*2; //1/50 consacré à la couleur autour
	x = width() / 2 - radius;
	y = height() / 2 - radius;

	//on dessinne maintenant l'image au centre
	QPixmap pix("./rouge.jpg");
	painter.drawPixmap(x, y, radius * 2, radius * 2, pix);
	
}

void GemmesUI::resizeEvent(QResizeEvent* event) {
	// Appelez la fonction de base pour que l'événement soit correctement traité
	QWidget::resizeEvent(event);
	// Forcer un nouveau rendu lorsque la taille change
	update();
}