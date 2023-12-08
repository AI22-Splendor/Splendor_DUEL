#pragma once
#include <qdialog.h>
#include <qlineedit.h>
#include "SplendorDuel.h"
#include <qcheckbox.h>
#include <qevent.h>
#include <qcombobox.h>
class MenuUI : public QDialog
{
	Q_OBJECT

public:
	MenuUI(QWidget* parent=nullptr);
	~MenuUI() { std::cout << "destroy"; }
	inline const string getP1name()const { return P1name.text().toStdString(); }
	inline const string getP2name()const { return P2name.text().toStdString(); }
	inline const bool IA()const { return ia.isChecked();}
	inline string getLanguage()const { return list.currentText().toStdString(); }
private:
	QComboBox list;
	QCheckBox ia;
	QLineEdit P1name;
	QLineEdit P2name;
};

