#pragma once
#include <qwidget.h>

class PlayerPoints : public QWidget
{
	Q_OBJECT

public:
	PlayerPoints(QWidget* parent);
	~PlayerPoints();

	void addCouronne(const int nb);
	void addPrestiges(const int nb);
	void setPoints(const int nb);
	inline const int getPoints()const { return nbPoints; };
private:
	int nbPoints, nbCourronne, nbPrestiges;
	void paintEvent(QPaintEvent* event);
};

