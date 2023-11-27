#pragma once
#include <qpixmap.h>
#include "Gemmes.h"
/// <summary>
/// classe singleton stockant toutes nos images souvent réutilisé
/// cela permet de les charger une seule fois pour notre projet et de limiter
/// le temps de chargement pendant le jeu
/// </summary>
class Image
{
public:
	/// <summary>
	/// retourne l'image de la gemmes donné
	/// </summary>
	/// <param name="g">la gemme</param>
	/// <returns>l'image</returns>
	static QPixmap getPixmap(const Gemmes g);

	/// <summary>
	/// retourn l'image du plateau
	/// </summary>
	/// <returns> retourne l'image du plateau</returns>
	static QPixmap getPlateau();

	/// <summary>
	/// retourne l'image de RemplirBoardUI
	/// </summary>
	/// <returns>l'image</returns>
	static QPixmap getUnderPlateau();

	/// <summary>
	/// retourne juste l'image de l'action remplir
	/// </summary>
	/// <returns>l'image</returns>
	static QPixmap getRemplir();

	/// <summary>
	/// retourne le fond des gemmes des joueurs
	/// </summary>
	/// <returns>l'image</returns>
	static QPixmap getPlayerGems();

	/// <summary>
	/// detruit notre singleton
	/// </summary>
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

