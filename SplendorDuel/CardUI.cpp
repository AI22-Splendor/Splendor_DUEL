#include "CardUI.h"
#include <qpainter.h>
#include "GemmesContainerGUI.h"
#include "Image.h"
#include "MyException.h"
#include <qevent.h>

CardUI::CardUI(CardContainersGUI* parent, int ligne, int col, bool details)
    :col(col), ligne(ligne), showDetails(details), selected(false), nbCard(0), QWidget(parent), cardList(), totalReduc(0), totalPoints(0), err(false), nbErr(0) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(QSize(20, 30));
}

CardUI::~CardUI() {}

void CardUI::mousePressEvent(QMouseEvent* mouse) {
    CardContainersGUI* parentGem = dynamic_cast<CardContainersGUI*>(parentWidget());
    if (parentGem) {
        if (!cardList.isEmpty() && mouse->button() == Qt::LeftButton) {
            parentGem->clickCard(this->col, this->ligne, this->cardList.at(cardList.size() - 1));
        }
        else if (mouse->button() == Qt::RightButton) {
            parentGem->clickDCard(this->col, this->ligne, this->cardList.at(cardList.size() - 1));
        }
    }
}

void CardUI::enterEvent(QEnterEvent* event) {
    if (!selected) {
        selected = true;
        update();
    }
}

void CardUI::leaveEvent(QEvent* event) {
    if (selected) {
        selected = false;
        update();
    }
}

void CardUI::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (cardList.size() == 0) {
        if (selected) {
            painter.drawPixmap(0, 0, width(), height(), Image::getCarteVide());
        }
        else {
            painter.drawPixmap(width() / 5, height() / 6, width() / 5 * 3, height() / 6 * 4, Image::getCarteVide());
        }
        return;
    }

    if (!selected) {
        QRect rect(width() / 5, height() / 5, width() / 5 * 3, height() / 5 * 3);
        int cardSpaceBetwin = rect.height() / (nbCard*2);
        int i = 1;
        for (const Card* c : cardList) {
            QPixmap pix= Image::getImageFromSrc(c->getImageSrc());
            painter.drawPixmap(rect.left(), rect.top()+cardSpaceBetwin*(i-1), rect.width(), rect.height()- cardSpaceBetwin*(nbCard-1), pix);
            i++;
        }
        if (this->err == true) {
            QColor c(Qt::red);
            c.setAlpha(99);
            painter.setBrush(c);
            painter.drawRect(rect);
        }
    }
    else {
        //si on survol on montre que la dernière ajouté au paquet
        QPixmap pix = Image::getImageFromSrc(cardList.at(nbCard-1)->getImageSrc());
        painter.drawPixmap(0, 0, width(), height(), pix);

        //si l'utilisateur le veux et que le nombre de points ou de reduc de la pile >0
        //on affiche le détails des réduction de ce paquet de cartes
        if ((totalReduc > 0 || totalPoints>0) && showDetails) {
            // Configurer la police et la taille du texte
            painter.setRenderHint(QPainter::TextAntialiasing);
            painter.setBackgroundMode(Qt::TransparentMode);
            QFont font = painter.font();
            font.setBold(true);
            font.setPointSize(width() / 5);  // Utiliser un quart de la largeur pour la taille du texte
            painter.setFont(font);

            // Obtenir la taille du texte rendu
            QRect textRect = painter.boundingRect(rect(), Qt::AlignTop | Qt::AlignRight, QString::number(totalReduc));
            painter.setBrush(QColor(pix.toImage().pixel(62, 0)));
            // Dessiner le texte dans le coin en haut à droite
            if (totalReduc > 0) {
                painter.setPen(QColor("#ffffff"));
                painter.drawText(QRect(width() - width()/10- textRect.width(), height() / 40, textRect.width(), textRect.height()), QString::number(totalReduc));
            }
            // Obtenir la taille du texte rendu
            textRect = painter.boundingRect(rect(), Qt::AlignTop | Qt::AlignLeft, QString::number(totalPoints));
            // Dessiner le texte dans le coin en haut à gauche
            if (totalPoints > 0) {
                painter.setPen(Qt::NoPen);
                painter.drawRect(QRect(width() / 15, 0, textRect.width(), textRect.height()));
                painter.setPen(QColor("#ffffff"));
                painter.drawText(QRect(width() / 15, 0, textRect.width(), textRect.height()), QString::number(totalPoints));
            }
        }
        if (this->err == true) {
            QColor c(Qt::red);
            c.setAlpha(99);
            painter.setBrush(c);
            painter.drawRect(0, 0, width(), height());
        }
    }
}

void CardUI::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int min = qMin(width(), height()/3*2);
    
    resize(min, min + min / 2);
    update();
}

void CardUI::ajouterCarte(const Card* s) {
    if (s == nullptr)
        return;
    cardList.append(s);
    nbCard++;
    totalReduc += s->getDiscount();
    totalPoints += s->getPointsPrestige();
    update();
}

void CardUI::supprimerCarte(const Card* s) {
    if (cardList.contains(s)) {
        cardList.removeAll(s);
        nbCard--;
        totalReduc -= s->getDiscount();
        totalPoints -= s->getPointsPrestige();
        update();
    }
    else {
        throw MyException("Erreur : le chemin est introuvable dans la liste");
    }
}

void CardUI::showErr() {
    this->err = true;
    this->update();
    startTimer(150);
}

void CardUI::timerEvent(QTimerEvent* event) {
    if (nbErr == 5) {
        this->err = false;
        this->killTimer(event->timerId());
        nbErr = 0;
        update();
    }
    else {
        nbErr++;
        this->err = !err;
        this->update();
    }
}

bool CardUI::isVide() {
    return cardList.isEmpty();
}