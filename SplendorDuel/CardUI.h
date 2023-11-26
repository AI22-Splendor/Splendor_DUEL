#pragma once
#include <qwidget.h>
#include "GemmesUI.h"
#include "Card.h"
#include "qlist.h"

/// <summary>
/// Le tableau des gemmes du joueurs
/// c'est un GemmesContainerGUI
/// </summary>
class CardUI : public QWidget
{
	Q_OBJECT
public:
	CardUI(QWidget* parent, QString pix);
	void ajouterCarte(QString s);
	void supprimerCarte(QString s);
	~CardUI();

private:
	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	
	int nbCard;
	bool selected;
	QList<QString> pathList;
};

