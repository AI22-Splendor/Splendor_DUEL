#include "PlayerPoints.h"
#include <qpainter.h>
#include "Image.h"


PlayerPoints::PlayerPoints(QWidget* parent) : QWidget(parent), nbCourronne(0), nbPoints(0), nbPrestiges(0) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
PlayerPoints::~PlayerPoints() {

}

void PlayerPoints::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, width(), height(), Image::getPlayersPoints());

    // Configurer la police et la taille du texte
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setBackgroundMode(Qt::TransparentMode);
    QFont font = painter.font();
    font.setBold(true);
    font.setPointSize(width() / 15);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));

    // Obtenir la taille du texte rendu
    QRect textRect = painter.boundingRect(rect(), Qt::AlignTop, QString::number(nbPrestiges));
    painter.drawText(QRect(width() * 0.21 -textRect.width(), 0, textRect.width(), textRect.height()), QString::number(nbPrestiges));

    textRect = painter.boundingRect(rect(), Qt::AlignTop, QString::number(nbCourronne));
    painter.drawText(QRect(width() * 0.47 -textRect.width(), height() / 40, textRect.width(), textRect.height()), QString::number(nbCourronne));

    textRect = painter.boundingRect(rect(), Qt::AlignTop, QString::number(nbPoints));
    painter.drawText(QRect(width()*0.86 - textRect.width(), height() / 40, textRect.width(), textRect.height()), QString::number(nbPoints));
}


void PlayerPoints::addCouronne(const int nb) {
    nbCourronne+=nb;
    update();
}

void PlayerPoints::addPrestiges(const int nb) {
    nbPrestiges+=nb;
    update();
}

void PlayerPoints::setPoints(const int nb) {
    nbPoints = nb;
    update();
}
