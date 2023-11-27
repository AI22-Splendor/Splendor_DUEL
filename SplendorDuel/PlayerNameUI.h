#pragma once
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
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);

	QString name;
};

