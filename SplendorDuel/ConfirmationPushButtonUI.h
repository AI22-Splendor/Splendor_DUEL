#pragma once
#include <qpushbutton.h>
class ConfirmationPushButtonUI : public QPushButton
{
	Q_OBJECT
public:
	ConfirmationPushButtonUI(QWidget* parent= nullptr);
private:
	bool hover;
	void paintEvent(QPaintEvent* e);
	inline void enterEvent(QEnterEvent* e) {
		hover = true;
		update();
	}
	inline void leaveEvent(QEvent* e) {
		hover = false;
		update();
	}
};

