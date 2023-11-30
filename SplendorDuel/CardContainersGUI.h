#pragma once

#include <qwidget.h>
#include "Card.h"

/// <summary>
/// Widget avec 2 fonctions devant être redéfinie pour tous les conteneurs de gemmesUI
/// </summary>
class CardContainersGUI : public QWidget
{
public:
	CardContainersGUI(QWidget* parent) : QWidget(parent) {}
	virtual void clickDCard(int col, int ligne, Card* c) = 0;
	virtual void clickCard(int col, int ligne, Card* c) = 0;
};