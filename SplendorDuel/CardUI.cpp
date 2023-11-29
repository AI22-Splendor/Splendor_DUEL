#include "CardUI.h"
#include <qpainter.h>
#include "GemmesContainerGUI.h"
#include "Image.h"
#include "MyException.h"
#include <qevent.h>

CardUI::CardUI(CardContainersGUI* parent, int ligne, int col, bool details)
    :col(col), ligne(ligne), showDetails(details), selected(false), nbCard(0), QWidget(parent), cardList(), totalReduc(0), err(false), nbErr(0) {
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
    int diff = (nbCard > 1) ? static_cast<float>(width()) / 4 / nbCard : 0;
    if (cardList.size() == 0) {
        if (selected) {
            painter.drawPixmap(0, 0, width(), height(), Image::getCarteVide());
        }
        else {
            painter.drawPixmap(width() / 5, height() / 6, width() / 5 * 3, height() / 6 * 4, Image::getCarteVide());
        }
    }

    if (!selected) {
        int i = 0;
        for (const Card* c : cardList) {
            QPixmap pix= Image::getImageFromSrc(c->getImageSrc());
            painter.drawPixmap(width() / 5, height() / 6 + diff * i, width() / 5 * 3, height() / 6 * 4 - diff * nbCard, pix);
            i++;
        }
        if (this->err == true) {
            QColor c(Qt::red);
            c.setAlpha(99);
            painter.setBrush(c);
            painter.drawRect(width() / 5, height() / 6, width() / 5 * 3, height() / 6 * 4);
        }
    }
    else {
        int i = 1;
        for (const Card* c : cardList) {
            QPixmap pix = Image::getImageFromSrc(c->getImageSrc());
            painter.drawPixmap(0, diff * i, width(), height() - diff * nbCard, pix);
            if (i == nbCard && totalReduc>0 && showDetails) {
                painter.setPen(QColor("#ffffff"));
                // Configurer la police et la taille du texte
                QFont font = painter.font();
                font.setPointSize(width() / 5);  // Utiliser un quart de la largeur pour la taille du texte
                painter.setFont(font);

                // Obtenir la taille du texte rendu
                QRect textRect = painter.boundingRect(rect(), Qt::AlignTop | Qt::AlignRight, QString::number(totalReduc));

                // Dessiner le texte dans le coin en haut à droite
                painter.drawText(QRect(width()/4*3, diff * nbCard, textRect.width(), textRect.height()), QString::number(totalReduc));

            }
            i++;
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
    update();
}

void CardUI::supprimerCarte(const Card* s) {
    if (cardList.contains(s)) {
        cardList.removeAll(s);
        nbCard--;
        totalReduc -= s->getDiscount();
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