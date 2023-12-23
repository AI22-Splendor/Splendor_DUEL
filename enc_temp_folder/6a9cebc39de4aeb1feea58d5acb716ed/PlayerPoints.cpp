#include "PlayerPoints.h"
#include <qpainter.h>
#include "Image.h"
#include "GameHandler.h"
#include "SplendorDuel.h"

PlayerPoints::PlayerPoints(QWidget* parent, Player& player, int pnum) : player(player), pnum(pnum), CardContainersGUI(parent) {
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
    QRect textRect = painter.boundingRect(rect(), Qt::AlignTop, QString::number(player.getPrestige()));
    painter.drawText(QRect(width() * 0.21 -textRect.width(), 0, textRect.width(), textRect.height()), QString::number(player.getPrestige()));

    textRect = painter.boundingRect(rect(), Qt::AlignTop, QString::number(player.getNbCrowns()));
    painter.drawText(QRect(width() * 0.47 -textRect.width(), height() / 40, textRect.width(), textRect.height()), QString::number(player.getNbCrowns()));

    textRect = painter.boundingRect(rect(), Qt::AlignTop, QString::number(player.getHighestGemPrestigeCount()));
    painter.drawText(QRect(width()*0.86 - textRect.width(), height() / 40, textRect.width(), textRect.height()), QString::number(player.getHighestGemPrestigeCount()));
}


void PlayerPoints::updateCouronne(const int nb) {
    update();
}

void PlayerPoints::udpdatePrestiges(const int nb) {
    update();
}

void PlayerPoints::updatePoints(const int nb) {
    update();
}

void PlayerPoints::resizeEvent(QResizeEvent* event) {
    this->layout()->setContentsMargins(0, (height() / 3), 0, 0);
}

void PlayerPoints::clickCard(int col, int ligne, Card* c) {
    int pturn = SingletonGameHandler::getInstance().isPlayer1Turn() ? 0 : 1;
    if (pturn != this->pnum) {
        card[col]->showErr();
        return;
    }
    int n = SingletonGameHandler::getInstance().buyCard(c, col);
    if (n >= 0) {
        ((QGridLayout*)this->layout())->removeWidget(card[col]);
        card[col]->supprimerCarte(c);
        card[col]->deleteLater();
        card[col] = nullptr;
        this->layout()->update();
        SingletonGameHandler::getInstance().playerBuyReservCard(pturn);
        if (n > 0)
            SplendorDuel::addPlayerCard(c, pturn);
        SplendorDuel::refreshPlayersGems(pturn);
        SplendorDuel::refreshMessage();
        SplendorDuel::changePtour();
        update();
    }
    else {
        card[col]->showErr();
    }
}

void PlayerPoints::updateCard(Card* c) {
    for (int i = 0; i < 3; i++) {
        if (card[i] == nullptr) {
            card[i]= new CardUI(this, 1, i);
            card[i]->ajouterCarte(c);
            ((QGridLayout*)this->layout())->addWidget(card[i], 0, i);
            return;
        }
    }
}