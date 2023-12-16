#ifndef GEMMESCONTAINERGUI_H
#define GEMMESCONTAINERGUI_H

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
<<<<<<< HEAD
<<<<<<< Updated upstream
	virtual void clickGemmes(Gemmes g) = 0;
=======
	virtual bool clickGemmes(EnumGemmes g) = 0;
>>>>>>> Stashed changes
};
=======
	virtual void clickGemmes(EnumGemmes g) = 0;
	virtual void clickDGemmes() = 0;
	virtual void scroll(int nb) = 0;
};

#endif
>>>>>>> 837c85eb72fd14b5c5985edc33ba1f6b11654a39
