#pragma once
#include <qwidget.h>
#include "GemmesUI.h"
#include "Card.h"
#include <qtimer.h>
#include "qlist.h"
#include "GemmesContainerGUI.h"

/// <summary>
/// Le tableau des gemmes du joueurs
/// c'est un GemmesContainerGUI
/// </summary>
class CardUI : public QWidget
{
	Q_OBJECT
public:
	CardUI(GemmesContainerGUI* parent);
	void ajouterCarte(Card* s);
	void supprimerCarte(Card* s);
	~CardUI();
	void showErr();

private:
	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void timerEvent(QTimerEvent* event);

	bool err;
	int nbErr;
	int totalReduc;
	int nbCard;
	bool selected;
	QList<Card*> cardList;
};

