#include "CardUI.h"
#include <qpainter.h>
#include "GemmesContainerGUI.h"
#include "Image.h"
#include "MyException.h"

CardUI::CardUI(QWidget* parent, QString pix)
    : selected(false), nbCard(0), QWidget(parent), pathList() {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMinimumSize(QSize(20, 30));
    pathList.append("./Card1.png");
}

CardUI::~CardUI() {}

void CardUI::mousePressEvent(QMouseEvent* mouse) {
    GemmesContainerGUI* parentGem = dynamic_cast<GemmesContainerGUI*>(parentWidget());
    if (parentGem) {
        parentGem->clickCard();
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
    int diff = (nbCard > 0) ? static_cast<float>(width()) / 6 / nbCard : 0;

    painter.drawPixmap(0, 0, width(), height(), Image::getPlayerGems());

    if (!selected) {
        int i = 0;
        for (const QString& s : pathList) {
            QPixmap pix(s);
            painter.drawPixmap(width() / 5, height() / 6 + diff * i, width() / 5 * 3, height() / 6 * 4 - diff * nbCard, pix);
            i++;
        }
    }
    else {
        int i = 0;
        for (const QString& s : pathList) {
            QPixmap pix(s);
            painter.drawPixmap(0, diff * i, width(), height() - diff * nbCard, pix);
            if (i == nbCard) {
                painter.setPen(QColor("#ffffff"));
                // Configurer la police et la taille du texte
                QFont font = painter.font();
                font.setPointSize(width() / 5);  // Utiliser un quart de la largeur pour la taille du texte
                painter.setFont(font);

                // Obtenir la taille du texte rendu
                QRect textRect = painter.boundingRect(rect(), Qt::AlignTop | Qt::AlignRight, QString::number(4));

                // Dessiner le texte dans le coin en haut à droite
                painter.drawText(QRect(width()/4*3, diff * nbCard, textRect.width(), textRect.height()), QString::number(4));

            }
            i++;
        }
    }
}

void CardUI::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    int min = qMin(width(), height()/3*2);
    
    resize(min, min + min / 2);
    update();
}

void CardUI::ajouterCarte(QString s) {
    if (!pathList.contains(s)) {
        pathList.append(s);
        nbCard++;
        update();
    }
    else {
        throw MyException("Erreur : le chemin est déjà présent dans la liste");
    }
}

void CardUI::supprimerCarte(QString s) {
    if (pathList.contains(s)) {
        pathList.removeAll(s);
        nbCard--;
        update();
    }
    else {
        throw MyException("Erreur : le chemin est introuvable dans la liste");
    }
}
