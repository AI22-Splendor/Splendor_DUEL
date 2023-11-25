#pragma once
#include "GemmesUI.h"
#include <qwidget.h>
#include "Gemmes.h"
#include "GemmesContainerGUI.h"
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
	GemmesUI(int ligne, int col, GemmesContainerGUI* parent);

	inline ~GemmesUI() { QWidget::~QWidget(); }

	/// <summary>
	/// Modifie la gemmes affich� sur le plateau
	/// </summary>
	/// <param name="g">la gemme</param>
	void setGemmes(const Gemmes& g);

	inline const Gemmes getGemmes()const { return this->gem; };

	void setNb(const int nb);

	inline const int getNb()const { return nb; };
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	int col;
	int ligne;
	int nb;
	bool selected;
	Gemmes gem;

	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void isClicked();
};

