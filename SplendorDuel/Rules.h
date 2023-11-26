#pragma once
#include "Board.h"
#include "Action.h"
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
	static Action isPossibleTakeGems(const Board b, const int* posTab, Action action);
	static bool playerWon(const Player& player);
private:
	//on supprime le constructeur et le destructeur
	Rules()= delete;
	~Rules() = delete;
};

