#include "PlayerCardUI.h"

PlayerCardUI::PlayerCardUI(QWidget* parent) : GemmesContainerGUI(parent) {
	this->cards = new CardUI * [6]();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PlayerCardUI::~PlayerCardUI() {
	delete[] cards;
	QWidget::~QWidget();
}