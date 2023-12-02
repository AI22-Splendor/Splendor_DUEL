#pragma once
#include "Board.h"
#include "Action.h"
#include <qlist.h>
#include "GameHandler.h"
/// <summary>
/// Class contenant uniquement des methode static
/// Elle permet de calculer si oui ou non l'action est possible
/// </summary>
#include "Player.h"

class Rules
{
public:
	/// <summary>
	/// Calcule si la / les gemmes peuvent être récupérer en fonction de laction en cour
	/// </summary>
	/// <param name="b">le plateau</param>
	/// <param name="posTab">la / les positions des gemmes voulant être récupérer</param>
	/// <param name="action">l'action demander</param>
	/// <returns>l'action à faire, par défault l'action demandé</returns>
	static Action isPossibleTakeGems(const Board b, const int* posTab, QList<Action> action, Gemmes g);
	static bool playerWon(const Player& player);
	static bool playerHaveToSuppGems(const Player& player);
	static bool canBuyNoble(const Card& noble, const Player& player);
	static bool playerCanBuyCardAsign(const Player& player);
private:
	//on supprime le constructeur et le destructeur
	Rules()= delete;
	~Rules() = delete;
};

