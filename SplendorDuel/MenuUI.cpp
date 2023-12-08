#include "MenuUI.h"
#include <qformlayout.h>
#include <qlabel.h>
#include "XmlReader.h"

MenuUI::MenuUI(QWidget* parent): QDialog(parent), P2name(), ia(), P1name(this), list(this){
	setWindowFlag(Qt::Dialog, true);
	QFormLayout* form = new QFormLayout(this);
	form->addRow(tr("Player1 Name"), &P1name);

	QWidget* p2 = new QWidget(this);
	QHBoxLayout* box = new QHBoxLayout(p2);
	P2name.setParent(p2);
	ia.setParent(p2);
	box->addWidget(&P2name);
	box->addWidget(new QLabel("IA", p2));
	box->addWidget(&ia);
	form->addRow(tr("Player2 Name"), p2);

	QPushButton* b=new QPushButton("OK", this);
	connect(b, SIGNAL(clicked()), this, SLOT(accept()));
	form->addRow(tr("Valider"), b);
	for (string s : XmlReader::getLanguage()) {
		if(!s.empty())
			list.addItem(s.c_str());
	}
	form->addRow(tr("Langue"), &list);
}
