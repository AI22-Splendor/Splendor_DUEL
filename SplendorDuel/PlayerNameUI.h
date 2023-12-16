#ifndef PLAYERNAMEUI_H
#define PLAYERNAMEUI_H

#include <qwidget.h>
#include <qevent.h>
class PlayerNameUI : public QWidget
{
	Q_OBJECT
public:
	inline PlayerNameUI(QString name, QWidget* parent): QWidget(parent), name(name){
		setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		setMinimumSize(QSize(20, 20));
	}
	inline ~PlayerNameUI() { QWidget::~QWidget(); };
	inline void setTour(bool b) {
		if (b != tour) { tour = b; update(); }
	}


private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	bool tour;
	QString name;
};

#endif