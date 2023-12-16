#ifndef CARDUI_H
#define CARDUI_H

#include <qwidget.h>
#include "GemmesUI.h"
#include "Card.h"
#include <qtimer.h>
#include "qlist.h"
#include "CardContainersGUI.h"

/// <summary>
/// Le tableau des gemmes du joueurs
/// c'est un GemmesContainerGUI
/// </summary>
class CardUI : public QWidget
{
	Q_OBJECT
public:
	CardUI(CardContainersGUI* parent, int linge=-1, int col=-1, bool details=false);
	void ajouterCarte(Card* s);
	void supprimerCarte(Card* s);
	bool isVide();
	~CardUI();
	void showErr();
	friend class AI;

private:
	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void timerEvent(QTimerEvent* event);

	bool showDetails;
	int col, ligne;
	bool err;
	int nbErr;
	int totalReduc, totalPoints;
	int nbCard;
	bool selected;
	QList<Card*> cardList;
};

#endif