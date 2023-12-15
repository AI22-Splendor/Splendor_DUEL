#pragma once

#include <qwidget.h>
#include "Gemmes.h"

/// <summary>
/// Widget avec 2 fonctions devant �tre red�finie pour tous les conteneurs de gemmesUI
/// </summary>
class GemmesContainerGUI : public QWidget
{
public:
	GemmesContainerGUI(QWidget* parent) : QWidget(parent) {}
	virtual void hoverGemmes(const int pos, const bool red) = 0;
<<<<<<< Updated upstream
	virtual void clickGemmes(Gemmes g) = 0;
=======
	virtual bool clickGemmes(EnumGemmes g) = 0;
>>>>>>> Stashed changes
};