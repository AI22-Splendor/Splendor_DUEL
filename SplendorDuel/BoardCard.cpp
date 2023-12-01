#include "BoardCard.h"
#include <qgridlayout.h>
#include "GameHandler.h"
#include "SplendorDuel.h"
#include "Image.h"
#include <qpainter.h>

BoardCardUI::BoardCardUI(QWidget* parent) : CardContainersGUI(parent) {
	this->cards = new CardUI **[3]();
	this->cards[0] = new CardUI *[3]();
	this->cards[1] = new CardUI * [4]();
	this->cards[2] = new CardUI * [5]();

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setMinimumSize(20 * 6, 30*3);
	QGridLayout* g = new QGridLayout(this);
	this->setLayout(g);
	for (int i = 0; i < 3; i++) {
		//CardUI* c = new CardUI(this);
		//g->addWidget(c, i, 0);
	}
	for (int i = 0; i < 3; i++) {
		CardUI* c = new CardUI(this, 0, i);
		g->addWidget(c, 0, i+3);
		c->ajouterCarte(GameHandler::getInstance().getDisplayedCard(2, i));
		cards[0][i] = c;
	}

	for (int i = 0; i < 4; i++) {
		CardUI* c = new CardUI(this, 1, i);
		g->addWidget(c, 1, i+2);
		c->ajouterCarte(GameHandler::getInstance().getDisplayedCard(1, i));
		cards[1][i] = c;
	}

	for (int i = 0; i < 5; i++) {
		CardUI* c = new CardUI(this, 2, i);
		g->addWidget(c, 2, i+1);
		c->ajouterCarte(GameHandler::getInstance().getDisplayedCard(0, i));
		cards[2][i] = c;
	}

	g->setContentsMargins(0, 0, 0, 0);
	g->setSpacing(0);
}

BoardCardUI::~BoardCardUI() {
	for (int i = 0; i < 3; i++) {
		delete[] this->cards[i];
	}
	delete[] cards;
	QWidget::~QWidget();
}

void BoardCardUI::clickDCard(int col, int ligne, Card* c) {
	if (c == nullptr) {
		return;
	}
	int pturn = GameHandler::getInstance().isPlayer1Turn() ? 0 : 1;
	if (GameHandler::getInstance().reservCard(c, col)) {
		this->cards[ligne][col]->supprimerCarte(c);
		this->cards[ligne][col]->ajouterCarte(GameHandler::getInstance().getDisplayedCard(c->getLevel(), col));
		SplendorDuel::reservCard(c, pturn);
	}
	else {
		this->cards[ligne][col]->showErr();
	}
}

void BoardCardUI::clickCard(int col, int ligne, Card* c) {
	if (c == nullptr) {
		cout << "Carte null";
		return;
	}
	int pturn = GameHandler::getInstance().isPlayer1Turn() ? 0: 1;
	int n = GameHandler::getInstance().buyCard(c, col);
	if (n>=0) {
		this->cards[ligne][col]->supprimerCarte(c);
		this->cards[ligne][col]->ajouterCarte(GameHandler::getInstance().getDisplayedCard(c->getLevel(), col));
		if(n>0)
			SplendorDuel::addPlayerCard(c, pturn);
		SplendorDuel::changePtour();
		SplendorDuel::refreshPlayersGems(pturn);
	}
	else{
		this->cards[ligne][col]->showErr();
	}
}