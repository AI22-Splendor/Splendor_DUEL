#pragma once
#include "CardContainersGUI.h"
#include "CardUI.h"
#include <qgridlayout.h>
class PlayerPoints : public CardContainersGUI
{
	Q_OBJECT

public:
	PlayerPoints(QWidget* parent);
	~PlayerPoints();

	void addCouronne(const int nb);
	void addPrestiges(const int nb);
	void setPoints(const int nb);
	void addCard(Card* c);
	inline const int getPoints()const { return nbPoints; };
private:
	void clickDCard(int col, int ligne, Card* c){}
	void clickCard(int col, int ligne, Card* c);
	int nbPoints, nbCourronne, nbPrestiges;
	CardUI** card;
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
};

