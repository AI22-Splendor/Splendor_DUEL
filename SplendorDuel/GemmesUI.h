#pragma once

#include <qlabel.h>
#include "Gemmes.h"
#include <qlineedit.h>
#include "StyleDecorator.h"
class GemmesUI : public QWidget
{
	Q_OBJECT

public:
	/// <summary>
	/// Met la gemmes en noir ou rouge
	/// </summary>
	/// <param name="red">si oui rouge, sinon noir</param>
	void hover(bool red);

	/// <summary>
	/// Represente une gemme sur le board
	/// </summary>
	/// <param name="ligne">la ligne correspondante</param>
	/// <param name="col">la collonne correspondante</param>
	GemmesUI(int ligne, int col, QWidget* parent);

	~GemmesUI();

	/// <summary>
	/// Modifie la gemmes affiché sur le plateau
	/// </summary>
	/// <param name="g">la gemme</param>
	void setGemmes(const Gemmes& g);
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	int col;
	int ligne;
	bool selected;
	Gemmes gem;

	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void isClicked();
};

