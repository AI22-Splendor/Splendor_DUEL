#ifndef CONFIRMATIONPUSHBUTTON_H
#define CONFIRMATIONPUSHBUTTON_H

#include <qpushbutton.h>
class ConfirmationPushButtonUI : public QPushButton
{
	Q_OBJECT
public:
	ConfirmationPushButtonUI(QWidget* parent= nullptr, const char* text="Valider");
private:
	bool hover;
	const QString text;
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

#endif