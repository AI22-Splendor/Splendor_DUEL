#ifndef FINPARTIE_H
#define FINPARTIE_H
#include <qdialog.h>

class FinPartie : public QDialog
{
	Q_OBJECT

public:
	FinPartie();

private:
	void paintEvent(QPaintEvent* e);
};

#endif

