#include "PlayerPoints.h"
#include <qpainter.h>
#include "Image.h"
#include "GameHandler.h"
#include "SplendorDuel.h"

PlayerPoints::PlayerPoints(QWidget* parent, int pnum) : pnum(pnum), CardContainersGUI(parent), nbCourronne(0), nbPoints(0), nbPrestiges(0) {
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QGridLayout* grid = new QGridLayout(this);
    card = new CardUI*[3]();
    this->setLayout(grid);
    grid->setSpacing(0);
    
    grid->setAlignment(Qt::AlignBottom);
    grid->setContentsMargins(0, (height()/3), 0, 0);
}
PlayerPoints::~PlayerPoints() {
    delete[] card;
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

void PlayerPoints::resizeEvent(QResizeEvent* event) {
    this->layout()->setContentsMargins(0, (height() / 3), 0, 0);
}

void PlayerPoints::clickCard(int col, int ligne, Card* c) {
    int pturn = GameHandler::getInstance().isPlayer1Turn() ? 0 : 1;
    if (pturn != this->pnum) {
        card[col]->showErr();
        return;
    }
    int n = GameHandler::getInstance().buyCard(c, col);
    if (n >= 0) {
        ((QGridLayout*)this->layout())->removeWidget(card[col]);
        card[col]->deleteLater();
        card[col]->supprimerCarte(c);
        card[col] = nullptr;
        this->layout()->update();
        GameHandler::getInstance().playerBuyReservCard(pturn);
        if (n > 0)
            SplendorDuel::addPlayerCard(c, pturn);
        SplendorDuel::changePtour();
        SplendorDuel::refreshPlayersGems(pturn);
        update();
    }
    else {
        card[col]->showErr();
    }
}

void PlayerPoints::addCard(Card* c) {
    for (int i = 0; i < 3; i++) {
        if (card[i] == nullptr) {
            card[i]= new CardUI(this, 1, i);
            card[i]->ajouterCarte(c);
            ((QGridLayout*)this->layout())->addWidget(card[i], 0, i);
            return;
        }
    }
}