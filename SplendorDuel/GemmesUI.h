#ifndef GEMMESUI_H
#define GEMMESUI_H

#include "GemmesUI.h"
#include <qwidget.h>
#include "Gemmes.h"
#include <qtimer.h>
#include "GemmesContainerGUI.h"

/// <summary>
/// Classe représentant un Gemmes en UI
/// elle doit être contenue dans un GemmesContainersGUI afin qui gerera ses event comme il le souhait
/// pour pouvoir être utilisé dans différente occasion
/// </summary>
class GemmesUI : public QWidget
{
	Q_OBJECT

public:
	/// <summary>
	/// Met la gemmes en noir ou rouge
	/// </summary>
	/// <param name="red">si oui rouge, sinon noir</param>
	void hover(const bool red);

	/// <summary>
	/// Represente une gemme sur le board
	/// </summary>
	/// <param name="ligne">la ligne correspondante</param>
	/// <param name="col">la collonne correspondante</param>
	GemmesUI(const int ligne, const int col, GemmesContainerGUI* parent);

	/// <summary>
	/// destrcuteur
	/// </summary>
	inline ~GemmesUI() { QWidget::~QWidget(); }

	/// <summary>
	/// Modifie la gemmes affiché sur le plateau
	/// </summary>
	/// <param name="g">la gemme</param>
	void setGemmes(const EnumGemmes& g);

	/// <summary>
	/// retourne la gemmes contenue
	/// </summary>
	inline const EnumGemmes getGemmes()const { return this->gem; };

	/// <summary>
	/// change le nombre a afficher
	/// </summary>
	/// <param name="nb">le nombre</param>
	void setNb(const int nb);

	/// <summary>
	/// affiche que l'action est pas possible en entourant en rouge
	/// </summary>
	void showErr();

	/// <summary>
	/// retourne le nombre
	/// </summary>
	/// <returns>le nombre</returns>
	inline const int getNb()const { return nb; };
private:
	void paintEvent(QPaintEvent* event);
	int col;
	int ligne;
	int nb;

	//savoir si elle est survoler
	bool selected;
	EnumGemmes gem;
	bool err;
	int nbErr;

	void wheelEvent(QWheelEvent* e);
	void mousePressEvent(QMouseEvent* mouse);
	void enterEvent(QEnterEvent* event);
	void leaveEvent(QEvent* event);
	void isClicked();
	void timerEvent(QTimerEvent* event);
};

#endif
