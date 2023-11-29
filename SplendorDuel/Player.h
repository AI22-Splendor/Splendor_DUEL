#pragma once

#include<string>
#include<list>
#include"Card.h"
#include"Gemmes.h"
#include "Bag.h"

using namespace std;

class Player {
public:
	/// <summary>
	/// Constructs a player 
	/// </summary>
	/// <param name="name">Name of the player</param>
	Player(string name);

	/// <summary>
	/// Returns the name of the player
	/// </summary>
	/// <returns>Name of the player</returns>
	string getName() const { return name; }

	/// <summary>
	/// Returns the number of gems of a certain type that the player currently have
	/// </summary>
	/// <param name="gem">Type of the gem</param>
	/// <returns>The number of gems that the player currently has</returns>
	unsigned int nbOfGems(const Gemmes gem) const { return gems[gem]; }

	/// <summary>
	/// Retursn a list of the currently owned cards of the player
	/// </summary>
	const list<const Card*>& getCards() const { return cards; }

	/// <summary>
	/// Checks if we can add gems to the player's gems
	/// </summary>
	/// <param name="nbAdd">Number of gems to add (by default 1)</param>
	/// <returns>True is the gems can be added, false if not</returns>
	int canAddGems(const unsigned int nbAdd = 1) const;

	/// <summary>
	/// Adds gems to the usér's gems
	/// </summary>
	/// <pre>We can add this amount of gems to the player</pre>
	/// <param name="gem">Type of the gem to add</param>
	/// <param name="nbAdd">Number of gems to add (by default 1)</param>
	/// <returns>True if the gems were added, false if not</returns>
	bool addGems(const Gemmes gem, const unsigned int nbAdd = 1);

	/// <summary>
	/// Removes this gem from the player's inventory
	/// </summary>
	/// <param name="gem">Gem to remove</param>
	/// <param name="nbRemove">Number of gems to remove (by default 1)</param>
	/// <returns>True if the gem was removed, false if not</returns>
	bool removeGem(Gemmes gem, const unsigned int nbRemove = 1);
	
	/// <summary>
	/// Returns the number of crowns of the player 
	/// </summary>
	/// <returns>The number of crowns of the player</returns>
	unsigned int getNbCrowns() const;


	/// <summary>
	/// Returns the number of prestige of the player for a gem type (the multi discount gem type included in all of them)
	/// </summary>
	/// <param name=gem>Gem type to investigate (by default Gemmes::Vide), if nothing is entered, we count the sum for all the gems</param>
	/// <returns>The number of prestige of the player for the specific gem type</returns>
	unsigned int getPrestige(Gemmes gem = Gemmes::Vide) const;

	/// <summary>
	/// Returns the total discount on a type of gem
	/// </summary>
	/// <param name="gem">Type of the discount</param>
	/// <returns>The total discount of the player</returns>
	unsigned int getDiscount(Gemmes gem) const;
	
	/// <summary>
	/// Checks if the player can buy the card
	/// </summary>
	/// <param name="card">Card to buy</param>
	/// <returns>True if the player can buy the card, false if not</returns>
	bool canBuyCard(const Card& card) const;

	/// <summary>
	/// Buys the card for the player, so adds it to the player's inventory 
	/// and deduces the correct his gems while putting them back in the bag
	/// </summary>
	/// <pre>Can buy the card</pre>
	/// <param name="card">Card to buy</param>
	/// <param name="gameBag">Bag to fill with the removed gems</param>
	/// <returns>True if bought the card correctly, false if not</returns>
	bool buyCard(const Card& card, Bag& gameBag);

	/// <summary>
	/// retourne le nombre de gemmes en possesion du joueur
	/// </summary>
	/// <returns></returns>
	unsigned int getNBGemmes()const;

	bool operator==(const Player& player) { return name.compare(player.name) == 0; }

// Protected for future possible AI impl
protected:
	string name;
	list<const Card*> cards;
	unsigned int gems[NB_GEMMES_PAS_VIDE];
};

