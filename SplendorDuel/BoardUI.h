#pragma once
#include "GemmesContainerGUI.h"
#include <qwidget.h>
#include "qpainter.h"
#include "Board.h"
#include "GemmesUI.h"
#include "RemplirBoardUI.h"

/// <summary>
/// Class affichant notre plateau
/// elle contient des GemmesUI donc est un GemmesContainerGUI
/// </summary>
class BoardUI: public GemmesContainerGUI
{

	Q_OBJECT

public:
	BoardUI(QWidget* parent);
	~BoardUI();
	/// <summary>
	/// r�affiche toutes nos gemmes avec le Board donn�
	/// </summary>
	/// <param name="b">le board</param>
	void setGemmes(const Board& b);

	/// <summary>
	/// quand une gemmes est survoler on retient sa postion dans le tableau des gemmes selectionner
	/// on demande au GH le nombre de gemme � selectionner
	/// </summary>
	/// <param name="pos">sa postiotion</param>
	/// <param name="red">si elle est survoler ou pas</param>
	void hoverGemmes(const int pos, const bool red);

	/// <summary>
	/// change la direction de selection des gemmes
	/// </summary>
	void changeDirection();

	/// <summary>
	/// change le nombre de gemmes selectionner
	/// </summary>
	void changeNbGemmes();

	/// <summary>
	/// une gemmes est clicker
	/// on donne donc l'information au GH avec le tableau des gemmes selectionner et si il les retire (renvoie true)
	/// on les supprime visuelement et donne l'info a SplendorDuel de les ajout� au Joueur qui joue
	/// </summary>
	/// <param name="g"> la gemme clicker</param>
<<<<<<< Updated upstream
	void clickGemmes(Gemmes g);
=======
	bool clickGemmes(EnumGemmes g);
>>>>>>> Stashed changes
	
private:
	void paintEvent(QPaintEvent* event);
	void resizeEvent(QResizeEvent* event);
	void selectOtherGemmes(const int pos);
	//tableau � deux dimensions
	GemmesUI*** tabCase;
	//RemplirBoard *unboard;

	//les direction possible
	enum direction {
		HORIZONTAL = 0,
		VERTICALE = 1,
		DIAGONALED = 2,
		DIAGONALEL = 3
	};
	int nbGemmes;
	direction direction;
	//tableau des gemmes selectionner
	int posSelect[3];
	friend class AI;
};

