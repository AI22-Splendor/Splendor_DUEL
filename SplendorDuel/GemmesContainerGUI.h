#ifndef GEMMESCONTAINERGUI_H
#define GEMMESCONTAINERGUI_H

#include <qwidget.h>
#include "Gemmes.h"

/// <summary>
/// Widget avec 2 fonctions devant être redéfinie pour tous les conteneurs de gemmesUI
/// </summary>
class GemmesContainerGUI : public QWidget
{
public:
	GemmesContainerGUI(QWidget* parent) : QWidget(parent) {}
	virtual void hoverGemmes(const int pos, const bool red) = 0;
	virtual void clickGemmes(EnumGemmes g) = 0;
	virtual void clickDGemmes() = 0;
	virtual void scroll(int nb) = 0;
};

#endif