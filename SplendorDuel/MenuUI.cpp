#include "MenuUI.h"
#include <qformlayout.h>
#include <qlabel.h>
#include "XmlReader.h"
#include <qpainter.h>
#include "BackgroundWidgetUI.h"
#include "ConfirmationPushButtonUI.h"

MenuUI::MenuUI(QWidget* parent): QDialog(parent), P2name("Player 2", nullptr), ia(), P1name("Player 1", this), list(this) {
	setWindowFlag(Qt::Dialog, true);
	setMinimumSize(350, 300);
	QVBoxLayout* vbox = new QVBoxLayout(this);
	QWidget* p2 = new QWidget(this);
	QHBoxLayout* box = new QHBoxLayout(p2);
	P2name.setParent(p2);
	ia.setParent(p2);
	ia.addItem("Joueur");
	ia.addItem("IA");
	box->addWidget(&P2name);
	box->addWidget(&ia);

	vbox->addWidget(&P1name);
	vbox->addWidget(p2);

	QPushButton* b=new ConfirmationPushButtonUI(this);
	connect(b, SIGNAL(clicked()), this, SLOT(accept()));
	
	for (string s : XmlReader::getLanguage()) {
		if(!s.empty())
			list.addItem(s.c_str());
	}
	vbox->addWidget(&list);
	vbox->addWidget(b);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void MenuUI::paintEvent(QPaintEvent* e) {
	QPainter painter(this);
	painter.drawPixmap(0, 0, width(), height(), QPixmap("./res/Menu.png"));
}