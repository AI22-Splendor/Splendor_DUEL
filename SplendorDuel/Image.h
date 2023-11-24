#pragma once
#include <qpixmap.h>
#include "Gemmes.h"
class Image
{
public:
	static QPixmap getPixmap(const Gemmes g);
	static QPixmap getPlateau();
	static QPixmap getUnderPlateau();
	static QPixmap getRemplir();
	static QPixmap getPlayerGems();
	static void destroy();
private:
	Image();
	~Image();
	static Image* instance;

	QPixmap blanc;
	QPixmap remplir;
	QPixmap noir;
	QPixmap rouge;
	QPixmap vert;
	QPixmap perle;
	QPixmap gold;
	QPixmap bleu;
	QPixmap plateau;
	QPixmap playerGems;
	QPixmap underPlat;
};

