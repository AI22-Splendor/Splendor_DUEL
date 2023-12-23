#ifndef CARDCONTAINERGUI_H
#define CARDCONTAINERGUI_H

#include <qwidget.h>
#include "Card.h"

/// <summary>
/// Widget avec 2 fonctions devant être redéfinie pour tous les conteneurs de gemmesUI
/// </summary>
class CardContainerGUI : public QWidget
{
public:
	CardContainerGUI(QWidget* parent) : QWidget(parent) {}
	virtual void clickDCard(int col, int ligne, Card* c) = 0;
	virtual void clickCard(int col, int ligne, Card* c) = 0;
};

#endif