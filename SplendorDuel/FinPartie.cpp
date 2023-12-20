#include "FinPartie.h"
#include "ConfirmationPushButtonUI.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include "GameHandler.h"
#include "Player.h"
#include <qpainter.h>

FinPartie::FinPartie(): QDialog(nullptr) {
	setWindowFlag(Qt::Dialog, true);
	setMinimumSize(350, 300);
	QGridLayout* grid = new QGridLayout(this);
	const Player& p = SingletonGameHandler::getInstance().getWinner();
	QString text = "Le joueur ";
	text.append(p.getName());
	text.append(" a gagné avec :");
	if (p.getNbCrowns() >= 10) {
		text.append(QString::number(p.getNbCrowns()));
		text.append(" Couronnes");
	}
	else if (p.getPrestige() >= 20) {
		text.append(QString::number(p.getPrestige()));
		text.append(" Prestiges");
	}
	else {
		for (int i = 0; i < NB_GEMMES_PAIEMENTS; i++) {
			if (p.getPrestige(static_cast<EnumGemmes>(i))>=10) {
				text.append(QString::number(p.getPrestige(static_cast<EnumGemmes>(i))));
				text.append(" Prestiges de Couleur ");
				text.append(gemmesToQstr(static_cast<EnumGemmes>(i)));
			}
		}
	}

	QLabel* label = new QLabel(text, this);
	QPushButton* replay = new ConfirmationPushButtonUI(this, "Rejouer");
	connect(replay, SIGNAL(clicked()), this, SLOT(accept()));
	QPushButton* quit = new ConfirmationPushButtonUI(this, "Quitter");
	connect(quit, SIGNAL(clicked()), this, SLOT(close()));

	grid->addWidget(label, 1, 1);
	QWidget* h = new QWidget(this);
	grid->addWidget(h, 2, 1);
	QHBoxLayout* hbox = new QHBoxLayout(h);
	//hbox->addWidget(replay);
	hbox->addWidget(quit);
}

void FinPartie::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, width(), height(), QPixmap("./res/Menu.png"));
}